using System;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Recv2
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MyForm());
        }
    }
    public class MyForm : Form
    {
        Label lbSt, lbPath, lbSize, lbHelp;
        Timer tm1;

        int st1 = 1, st2 = 1;
        StringBuilder sb = new StringBuilder();
        public MyForm()
        {
            FormBorderStyle = FormBorderStyle.None;
            WindowState = FormWindowState.Maximized;

            int w = SystemInformation.VirtualScreen.Width, h = SystemInformation.VirtualScreen.Height;
            rUL = new Rectangle(0, 0, SZ, SZ);
            rUR = new Rectangle(w - SZ, 0, SZ, SZ);
            rBL = new Rectangle(0, h - SZ, SZ, SZ);
            rBR = new Rectangle(w - SZ, h - SZ, SZ, SZ);
            b0 = new SolidBrush(Color.Black);
            bR = new SolidBrush(Color.Red);
            bG = new SolidBrush(Color.Green);
            bB = new SolidBrush(Color.Blue);
            bUL = b0;
            bUR = b0;

            Font font = new Font("宋体", 12F);
            int x = 100;

            lbSt = new Label();
            lbSt.AutoSize = true;
            lbSt.Text = "IDLE";
            lbSt.Location = new Point(x, 100);
            lbSt.Font = font;

            lbPath = new Label();
            lbPath.AutoSize = true;
            lbPath.Text = "** ready **";
            lbPath.Location = new Point(x, 140);
            lbPath.Font = font;

            lbSize = new Label();
            lbSize.AutoSize = true;
            lbSize.Text = lbPath.Text;
            lbSize.Location = new Point(x, 160);
            lbSize.Visible = false;
            lbSize.Font = font;

            lbHelp = new Label();
            lbHelp.AutoSize = true;
            lbHelp.Text = "[Esc] = Exit";
            lbHelp.Location = new Point(x, 400);
            lbHelp.Font = font;

            tm1 = new Timer();
            tm1.Interval = 1000;
            tm1.Tick += new System.EventHandler(this.tm1_Tick);

            Controls.Add(lbSize);
            Controls.Add(lbPath);
            Controls.Add(lbSt);
            Controls.Add(lbHelp);

            Paint += new PaintEventHandler(OnPaint);
            KeyPress += new KeyPressEventHandler(OnKeyPress);
        }

        Brush b0, bR, bG, bB;
        Brush bUL, bUR;
        const int SZ = 20;
        Rectangle rUL, rUR, rBL, rBR;

        private void OnPaint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.FillRectangle(bUL, rUL);
            g.FillRectangle(bUR, rUR);
            g.FillRectangle(b0, rBL);
            g.FillRectangle(b0, rBR);
        }

        BinaryWriter bw = null;
        string path;
        int size;
        int recv;
        void CancelFile()
        {
            if (bw != null)
            {
                bw.Close();
                bw = null;
                File.Delete(path);
            }
        }
        void FSP(string s)
        {
            char t = s[0];
            string s2 = s.Substring(1);
            if (t == 'f')
            {
                CancelFile();

                string[] ss = s2.Split('|');
                path = @"D:\" + ss[0];
                size = Convert.ToInt32(ss[1]);
                recv = 0;
                lbPath.Text = "Path: " + path;
                lbSize.Text = "Received: 0/" + size;
                lbSize.Visible = true;

                bw = new BinaryWriter(new FileStream(path, FileMode.Create));
            }
            else if (t == 'd')
            {
                var buf = System.Convert.FromBase64String(s2);
                bw.Write(buf);
                recv += buf.Length;
                lbSize.Text = "Received: " + recv + "/" + size;
                if (recv >= size)
                {
                    lbPath.Text = "** succeed. next one! **";
                    lbSize.Visible = false;
                    bw.Close();
                    bw = null;
                }
            }
        }

        private void tm1_Tick(object sender, EventArgs e)
        {
            bUL = b0;
            st1 = 1;
            tm1.Enabled = false;
            if (st2 == 2)
            {
                st2 = 1;
                bUR = bR;
                lbSt.Text = "IDLE";
            }
            else if (st2 == 3)
            {
                st2 = 1;
                lbSt.Text = "IDLE";
            }
            Invalidate();
        }

        private void OnKeyPress(object sender, KeyPressEventArgs e)
        {
            if (st1 == 1 && e.KeyChar == '\x1B')
            {
                Application.Exit();
            }
            if (st1 == 1)
            {
                bUL = bR;
                st1 = 2;
                tm1.Enabled = true;
            }
            else
            {
                tm1.Enabled = false;
                tm1.Enabled = true;
            }
            char ch = e.KeyChar;
            if (st2 == 1)
            {
                if (ch == '<')
                {
                    sb.Clear();
                    st2 = 2;
                    bUR = b0;
                    lbSt.Text = "RECV 0";
                }
                else
                {
                    st2 = 3;
                    bUR = bR;
                    lbSt.Text = "WAIT";
                }
            }
            else if (st2 == 2)
            {
                if (ch == '>')
                {
                    st2 = 3;
                    bool pass = false;
                    if (sb.Length >= 4)
                    {
                        string s = sb.ToString();
                        string h = s.Substring(0, 4);
                        string d = s.Substring(4);
                        if (string.Format("{0:X8}", d.GetHashCode()).Substring(0, 4) == h)
                        {
                            FSP(d);
                            pass = true;
                        }
                    }
                    bUR = pass ? bG : bR;
                    lbSt.Text = "WAIT";
                }
                else
                {
                    sb.Append(ch);
                    lbSt.Text = "RECV " + sb.Length;
                }
            }
            Invalidate();
        }

        private void OnFormClosed(object sender, FormClosedEventArgs e)
        {
            CancelFile();
        }
    }
}
