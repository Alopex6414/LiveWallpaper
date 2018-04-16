/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		FormMain.cs
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.10a
* @date		2018-03-20	v1.00a	alopex	Create Project
*/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using Microsoft.Win32;

namespace LiveWallpaperUI
{
    public partial class FormMain : Form
    {
        [DllImport("User32", EntryPoint = "GetSystemMetrics")]
        private static extern int GetSystemMetrics(int nIndex);
        [DllImport("User32", EntryPoint = "SetWindowPos")]
        private static extern int SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int X, int Y, int cx, int cy, int uFlags);
        [DllImport("User32", EntryPoint = "SendMessage")]
        public static extern int SendMessage(IntPtr hwnd, int wMsg, int wParam, int lParam);
        [DllImport("User32.dll")]
        private static extern int ReleaseCapture();
        [DllImport("LiveUI.dll")]
        private static extern int LiveUIWriteConfigFile(string lpAppName, string lpKeyName, string lpString);
        [DllImport("LiveUI.dll")]
        private static extern int LiveUIReStartLiveCore();

        // Variable Definition
        private Rectangle m_MainRect;       //窗口矩形区域
        private Rectangle m_TitleRect;      //窗口标题栏矩形区域
        private Rectangle m_ToolRect;       //窗口工具栏矩形区域

        protected override CreateParams CreateParams
        {
            get
            {
                const int WS_MINIMIZEBOX = 0x00020000;  // Winuser.h中定义
                CreateParams cp = base.CreateParams;
                cp.Style = cp.Style | WS_MINIMIZEBOX;   // 允许最小化操作
                return cp;
            }
        }

        #region 窗口初始化
        public FormMain()
        {
            InitializeComponent();
        }
        #endregion

        #region 窗口加载
        private void FormMain_Load(object sender, EventArgs e)
        {
            FormMain_InitWindowSharp();
            FormMain_InitWindowTool();
            FormMain_InitAttribute();
        }
        #endregion

        #region 窗口重绘
        private void FormMain_Paint(object sender, PaintEventArgs e)
        {
            Graphics graphics = e.Graphics;
            SolidBrush SolidBrushMain = new SolidBrush(Color.FromArgb(245, 245, 245));
            SolidBrush SolidBrushTool = new SolidBrush(Color.FromArgb(39, 42, 47));

            graphics.FillRectangle(SolidBrushMain, m_MainRect);
            graphics.FillRectangle(SolidBrushTool, m_ToolRect);
        }
        #endregion

        // Function Definition

        // 初始化窗口形状
        private void FormMain_InitWindowSharp()
        {
            int nX = 0;
            int nY = 0;
            int nScreenWidth = 0;
            int nScreenHeight = 0;

            this.Width = 960;   //窗口宽度
            this.Height = 720;  //窗口高度

            nScreenWidth = GetSystemMetrics(0);     //屏幕宽度
            nScreenHeight = GetSystemMetrics(1);    //屏幕高度

            if (nScreenWidth >= this.Width && nScreenHeight >= this.Height)
            {
                nX = (nScreenWidth - this.Width) >> 1;
                nY = (nScreenHeight - this.Height) >> 1;
                SetWindowPos(this.Handle, (IntPtr)0, nX, nY, this.Width, this.Height, 64);  // 设置窗口初始位置
            }

            m_MainRect.X = 0;
            m_MainRect.Y = 0;
            m_MainRect.Width = this.Width;
            m_MainRect.Height = this.Height;
        }

        // 初始化窗口
        private void FormMain_InitWindowTool()
        {
            m_ToolRect.X = m_MainRect.X;
            m_ToolRect.Y = m_MainRect.Y;
            m_ToolRect.Width = 64;
            m_ToolRect.Height = m_MainRect.Height;

            m_TitleRect.X = m_ToolRect.Right;
            m_TitleRect.Y = m_MainRect.Y;
            m_TitleRect.Width = 862;
            m_TitleRect.Height = 34;
        }

        // 初始化窗口属性
        private void FormMain_InitAttribute()
        {
            // 窗体属性
            

            // 控件属性
            this.PanelTool.BackColor = Color.FromArgb(0, 39, 42, 47);       // 工具栏颜色
            this.PanelTitle.BackColor = Color.FromArgb(0, 235, 235, 235);   // 标题栏颜色
            this.PanelClose.BackColor = Color.FromArgb(0, 235, 235, 235);   // 关闭按钮背景颜色
            this.PanelIcon.BackColor = Color.FromArgb(0, 39, 42, 47);       // 图标颜色
        }

        // 关闭按钮-鼠标进入
        private void PanelClose_MouseEnter(object sender, EventArgs e)
        {
            this.PanelClose.BackgroundImage = Properties.Resources.close_hor;
        }

        // 关闭按钮-鼠标离开
        private void PanelClose_MouseLeave(object sender, EventArgs e)
        {
            this.PanelClose.BackgroundImage = Properties.Resources.close;
        }

        // 关闭按钮-鼠标悬停
        private void PanelClose_MouseHover(object sender, EventArgs e)
        {
            this.PanelClose.BackgroundImage = Properties.Resources.close_hor;
        }

        // 关闭按钮-鼠标按下
        private void PanelClose_MouseDown(object sender, MouseEventArgs e)
        {
            this.PanelClose.BackgroundImage = Properties.Resources.close_focus;
        }

        // 关闭按钮-鼠标单击
        private void PanelClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        // 关闭按钮重绘
        private void PanelClose_Paint(object sender, PaintEventArgs e)
        {

        }

        // 工具栏鼠标拖动
        private void PanelTool_MouseDown(object sender, MouseEventArgs e)
        {
            ReleaseCapture();
            SendMessage((IntPtr)this.Handle, 0x00A1, 0x0002, 0);
        }

        // 标题栏鼠标拖动
        private void PanelTitle_MouseDown(object sender, MouseEventArgs e)
        {
            ReleaseCapture();
            SendMessage((IntPtr)this.Handle, 0x00A1, 0x0002, 0);
        }

        // 最小化按钮-鼠标进入
        private void PannelMin_MouseEnter(object sender, EventArgs e)
        {
            this.PanelMin.BackgroundImage = Properties.Resources.min_hor;
        }

        // 最小化按钮-鼠标离开
        private void PannelMin_MouseLeave(object sender, EventArgs e)
        {
            this.PanelMin.BackgroundImage = Properties.Resources.min;
        }

        // 最小化按钮-鼠标悬停
        private void PannelMin_MouseHover(object sender, EventArgs e)
        {
            this.PanelMin.BackgroundImage = Properties.Resources.min_hor;
        }

        // 最小化按钮-鼠标按下
        private void PannelMin_MouseDown(object sender, MouseEventArgs e)
        {
            this.PanelMin.BackgroundImage = Properties.Resources.min_focus;
        }

        // 最小化按钮-鼠标单击
        private void PannelMin_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        // 最小化按钮-鼠标重绘
        private void PannelMin_Paint(object sender, PaintEventArgs e)
        {

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void CheckBoxDefault1_CheckedChanged(object sender, EventArgs e)
        {
            if(this.CheckBoxDefault1.Checked == true)
            {
                this.CheckBoxDefault2.Checked = false;
            }
        }

        private void CheckBoxDefault2_CheckedChanged(object sender, EventArgs e)
        {
            if (this.CheckBoxDefault2.Checked == true)
            {
                this.CheckBoxDefault1.Checked = false;
            }
        }

        private void CheckBoxShowMode1_CheckedChanged(object sender, EventArgs e)
        {
            if(this.CheckBoxShowMode1.Checked == true)
            {
                this.CheckBoxShowMode2.Checked = false;
                this.CheckBoxShowMode3.Checked = false;
                this.CheckBoxShowMode4.Checked = false;
                this.CheckBoxShowMode5.Checked = false;
            }
        }

        private void CheckBoxShowMode2_CheckedChanged(object sender, EventArgs e)
        {
            if (this.CheckBoxShowMode2.Checked == true)
            {
                this.CheckBoxShowMode1.Checked = false;
                this.CheckBoxShowMode3.Checked = false;
                this.CheckBoxShowMode4.Checked = false;
                this.CheckBoxShowMode5.Checked = false;
            }
        }

        private void CheckBoxShowMode3_CheckedChanged(object sender, EventArgs e)
        {
            if (this.CheckBoxShowMode3.Checked == true)
            {
                this.CheckBoxShowMode1.Checked = false;
                this.CheckBoxShowMode2.Checked = false;
                this.CheckBoxShowMode4.Checked = false;
                this.CheckBoxShowMode5.Checked = false;
            }
        }

        private void CheckBoxShowMode4_CheckedChanged(object sender, EventArgs e)
        {
            if (this.CheckBoxShowMode4.Checked == true)
            {
                this.CheckBoxShowMode1.Checked = false;
                this.CheckBoxShowMode2.Checked = false;
                this.CheckBoxShowMode3.Checked = false;
                this.CheckBoxShowMode5.Checked = false;
            }
        }

        private void CheckBoxShowMode5_CheckedChanged(object sender, EventArgs e)
        {
            if (this.CheckBoxShowMode5.Checked == true)
            {
                this.CheckBoxShowMode1.Checked = false;
                this.CheckBoxShowMode2.Checked = false;
                this.CheckBoxShowMode3.Checked = false;
                this.CheckBoxShowMode4.Checked = false;
            }
        }

        private void CheckBoxShowYes_CheckedChanged(object sender, EventArgs e)
        {
            if(this.CheckBoxShowYes.Checked == true)
            {
                this.CheckBoxShowNo.Checked = false;
            }

            this.NumberUpDownType.Enabled = true;
        }

        private void CheckBoxShowNo_CheckedChanged(object sender, EventArgs e)
        {
            if (this.CheckBoxShowNo.Checked == true)
            {
                this.CheckBoxShowYes.Checked = false;
            }

            this.NumberUpDownType.Enabled = false;
        }

        // 点击选择按钮
        private void ButtonOpen_Click(object sender, EventArgs e)
        {
            OpenFileDialog File = new OpenFileDialog();
            string FileName = "";

            File.InitialDirectory = "C:\\";
            File.Filter = "文件(*.mp4;*.wmv;*.mkv;*.mov;*.avi;*.rmvb)|(*.mp4;*.wmv;*.mkv;*.mov;*.avi;*.rmvb)||";
            File.FilterIndex = 1;
            File.RestoreDirectory = true;
            File.Multiselect = false;

            if(File.ShowDialog() == DialogResult.OK)
            {
                FileName = File.FileName;
                this.TextBoxFilePath.Text = FileName;
            }

        }

        // 点击开始按钮
        private void ButtonStart_Click(object sender, EventArgs e)
        {
            // 分析写入配置文件
            if (this.TextBoxFilePath.Text == "" && this.RadioButtonSelectMode.Checked == true)
            {
                MessageBox.Show("动态壁纸地址不能为空!");
                return;
            }

            // LiveWallpaper模式
            if (RadioButtonDefaultMode.Checked == true)
            {
                LiveUIWriteConfigFile("LIVECOREVIDEOADDRESS", "LiveCore_Video_Mode", "0");
            }
            else
            {
                LiveUIWriteConfigFile("LIVECOREVIDEOADDRESS", "LiveCore_Video_Mode", "1");
            }

            // LiveWallpaper示例壁纸选择
            if(CheckBoxDefault1.Checked == true)
            {
                LiveUIWriteConfigFile("LIVECOREVIDEOADDRESS", "LiveCore_Video_Name", "Wallpaper1.pak");
            }
            else
            {
                LiveUIWriteConfigFile("LIVECOREVIDEOADDRESS", "LiveCore_Video_Name", "Wallpaper2.pak");
            }

            // LiveWallpaper显示模式选择
            if(CheckBoxShowMode1.Checked == true)
            {
                LiveUIWriteConfigFile("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", "0");
            }
            else if(CheckBoxShowMode2.Checked == true)
            {
                LiveUIWriteConfigFile("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", "1");
            }
            else if(CheckBoxShowMode3.Checked == true)
            {
                LiveUIWriteConfigFile("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", "2");
            }
            else if(CheckBoxShowMode4.Checked == true)
            {
                LiveUIWriteConfigFile("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", "3");
            }
            else
            {
                LiveUIWriteConfigFile("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", "4");
            }

            // LiveWallpaper显示模式选择
            if(CheckBoxShowYes.Checked == true)
            {
                LiveUIWriteConfigFile("LIVECORESHOW", "LiveCore_Show_Graphics", "1");
            }
            else
            {
                LiveUIWriteConfigFile("LIVECORESHOW", "LiveCore_Show_Graphics", "0");
            }

            // LiveWallpaper显示模式选择
            string strNumber = this.NumberUpDownType.Value.ToString();
            LiveUIWriteConfigFile("LIVECORESHOW", "LiveCore_Show_GraphicsFont", strNumber);

            // LiveWallpaper播放音频模式
            if(this.CheckBoxAudioYes.Checked == true)
            {
                LiveUIWriteConfigFile("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Audio", "1");
            }
            else
            {
                LiveUIWriteConfigFile("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Audio", "0");
            }

            // LiveWallpaper播放视频地址
            string strAddress = this.TextBoxFilePath.Text;
            LiveUIWriteConfigFile("LIVECOREVIDEOADDRESS", "LiveCore_Video_Address", strAddress);

            LiveUIReStartLiveCore();
        }

        // 点击关闭按钮
        private void ButtonClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void RadioButtonDefaultMode_CheckedChanged(object sender, EventArgs e)
        {
            this.CheckBoxDefault1.Enabled = true;
            this.CheckBoxDefault2.Enabled = true;
            this.TextBoxFilePath.Enabled = false;
            this.ButtonOpen.Enabled = false;
        }

        private void RadioButtonSelectMode_CheckedChanged(object sender, EventArgs e)
        {
            this.CheckBoxDefault1.Enabled = false;
            this.CheckBoxDefault2.Enabled = false;
            this.TextBoxFilePath.Enabled = true;
            this.ButtonOpen.Enabled = true;
        }

        private void CheckBoxAudioYes_CheckedChanged(object sender, EventArgs e)
        {
            if(this.CheckBoxAudioYes.Checked == true)
            {
                this.CheckBoxAudioNo.Checked = false;
            }
        }

        private void CheckBoxAudioNo_CheckedChanged(object sender, EventArgs e)
        {
            if (this.CheckBoxAudioNo.Checked == true)
            {
                this.CheckBoxAudioYes.Checked = false;
            }
        }
    }
}
