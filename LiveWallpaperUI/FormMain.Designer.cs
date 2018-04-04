namespace LiveWallpaperUI
{
    partial class FormMain
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
            this.PanelTool = new System.Windows.Forms.Panel();
            this.PanelTitle = new System.Windows.Forms.Panel();
            this.PanelIcon = new System.Windows.Forms.Panel();
            this.PanelClose = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // PanelTool
            // 
            this.PanelTool.Location = new System.Drawing.Point(0, 0);
            this.PanelTool.Name = "PanelTool";
            this.PanelTool.Size = new System.Drawing.Size(64, 720);
            this.PanelTool.TabIndex = 1;
            this.PanelTool.MouseDown += new System.Windows.Forms.MouseEventHandler(this.PanelTool_MouseDown);
            // 
            // PanelTitle
            // 
            this.PanelTitle.Location = new System.Drawing.Point(64, 0);
            this.PanelTitle.Name = "PanelTitle";
            this.PanelTitle.Size = new System.Drawing.Size(862, 34);
            this.PanelTitle.TabIndex = 2;
            this.PanelTitle.MouseDown += new System.Windows.Forms.MouseEventHandler(this.PanelTitle_MouseDown);
            // 
            // PanelIcon
            // 
            this.PanelIcon.BackgroundImage = global::LiveWallpaperUI.Properties.Resources.SakuraIcon1;
            this.PanelIcon.Location = new System.Drawing.Point(16, 16);
            this.PanelIcon.Name = "PanelIcon";
            this.PanelIcon.Size = new System.Drawing.Size(32, 32);
            this.PanelIcon.TabIndex = 3;
            // 
            // PanelClose
            // 
            this.PanelClose.BackColor = System.Drawing.SystemColors.Control;
            this.PanelClose.BackgroundImage = global::LiveWallpaperUI.Properties.Resources.close;
            this.PanelClose.Location = new System.Drawing.Point(926, 0);
            this.PanelClose.Name = "PanelClose";
            this.PanelClose.Size = new System.Drawing.Size(34, 34);
            this.PanelClose.TabIndex = 0;
            this.PanelClose.Click += new System.EventHandler(this.PanelClose_Click);
            this.PanelClose.Paint += new System.Windows.Forms.PaintEventHandler(this.PanelClose_Paint);
            this.PanelClose.MouseDown += new System.Windows.Forms.MouseEventHandler(this.PanelClose_MouseDown);
            this.PanelClose.MouseEnter += new System.EventHandler(this.PanelClose_MouseEnter);
            this.PanelClose.MouseLeave += new System.EventHandler(this.PanelClose_MouseLeave);
            this.PanelClose.MouseHover += new System.EventHandler(this.PanelClose_MouseHover);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(960, 720);
            this.Controls.Add(this.PanelIcon);
            this.Controls.Add(this.PanelTitle);
            this.Controls.Add(this.PanelTool);
            this.Controls.Add(this.PanelClose);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "FormMain";
            this.Text = "LiveWallpaper";
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.FormMain_Paint);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel PanelClose;
        private System.Windows.Forms.Panel PanelTool;
        private System.Windows.Forms.Panel PanelTitle;
        private System.Windows.Forms.Panel PanelIcon;
    }
}

