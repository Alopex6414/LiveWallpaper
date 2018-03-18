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

        // Variable Definition
        private Rectangle m_MainRect;       //窗口矩形区域
        private Rectangle m_TitleRect;      //窗口标题栏矩形区域
        private Rectangle m_ToolRect;       //窗口工具栏矩形区域

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
            this.PanelTool.BackColor = Color.FromArgb(0, 39, 42, 47);       // 工具栏颜色
            this.PanelTitle.BackColor = Color.FromArgb(0, 245, 245, 245);   // 标题栏颜色
            this.PanelClose.BackColor = Color.FromArgb(0, 245, 245, 245);   // 关闭按钮背景颜色
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

    }
}
