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
            this.PanelMin = new System.Windows.Forms.Panel();
            this.PanelTitleText = new System.Windows.Forms.Panel();
            this.PanelIcon = new System.Windows.Forms.Panel();
            this.PanelClose = new System.Windows.Forms.Panel();
            this.PanelFrame = new System.Windows.Forms.Panel();
            this.ButtonClose = new System.Windows.Forms.Button();
            this.ButtonStart = new System.Windows.Forms.Button();
            this.GroupBoxFile = new System.Windows.Forms.GroupBox();
            this.NumberUpDownType = new System.Windows.Forms.NumericUpDown();
            this.LabelShowFont = new System.Windows.Forms.Label();
            this.CheckBoxShowNo = new System.Windows.Forms.CheckBox();
            this.CheckBoxShowYes = new System.Windows.Forms.CheckBox();
            this.LabelShowFrame = new System.Windows.Forms.Label();
            this.CheckBoxShowMode5 = new System.Windows.Forms.CheckBox();
            this.CheckBoxShowMode4 = new System.Windows.Forms.CheckBox();
            this.CheckBoxShowMode3 = new System.Windows.Forms.CheckBox();
            this.CheckBoxShowMode2 = new System.Windows.Forms.CheckBox();
            this.CheckBoxShowMode1 = new System.Windows.Forms.CheckBox();
            this.LabelShowMode = new System.Windows.Forms.Label();
            this.CheckBoxDefault2 = new System.Windows.Forms.CheckBox();
            this.CheckBoxDefault1 = new System.Windows.Forms.CheckBox();
            this.LabelDefaultSelect = new System.Windows.Forms.Label();
            this.RadioButtonSelectMode = new System.Windows.Forms.RadioButton();
            this.RadioButtonDefaultMode = new System.Windows.Forms.RadioButton();
            this.LableMode = new System.Windows.Forms.Label();
            this.LabelTitleFilePath = new System.Windows.Forms.Label();
            this.TextBoxFilePath = new System.Windows.Forms.TextBox();
            this.ButtonOpen = new System.Windows.Forms.Button();
            this.LabelFilePath = new System.Windows.Forms.Label();
            this.LabelPlaySound = new System.Windows.Forms.Label();
            this.CheckBoxAudioNo = new System.Windows.Forms.CheckBox();
            this.CheckBoxAudioYes = new System.Windows.Forms.CheckBox();
            this.PanelTitle.SuspendLayout();
            this.PanelFrame.SuspendLayout();
            this.GroupBoxFile.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NumberUpDownType)).BeginInit();
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
            this.PanelTitle.Controls.Add(this.PanelMin);
            this.PanelTitle.Controls.Add(this.PanelTitleText);
            this.PanelTitle.Location = new System.Drawing.Point(64, 0);
            this.PanelTitle.Name = "PanelTitle";
            this.PanelTitle.Size = new System.Drawing.Size(862, 34);
            this.PanelTitle.TabIndex = 2;
            this.PanelTitle.MouseDown += new System.Windows.Forms.MouseEventHandler(this.PanelTitle_MouseDown);
            // 
            // PanelMin
            // 
            this.PanelMin.BackgroundImage = global::LiveWallpaperUI.Properties.Resources.min;
            this.PanelMin.Location = new System.Drawing.Point(828, 0);
            this.PanelMin.Name = "PanelMin";
            this.PanelMin.Size = new System.Drawing.Size(34, 34);
            this.PanelMin.TabIndex = 4;
            this.PanelMin.Click += new System.EventHandler(this.PannelMin_Click);
            this.PanelMin.Paint += new System.Windows.Forms.PaintEventHandler(this.PannelMin_Paint);
            this.PanelMin.MouseDown += new System.Windows.Forms.MouseEventHandler(this.PannelMin_MouseDown);
            this.PanelMin.MouseEnter += new System.EventHandler(this.PannelMin_MouseEnter);
            this.PanelMin.MouseLeave += new System.EventHandler(this.PannelMin_MouseLeave);
            this.PanelMin.MouseHover += new System.EventHandler(this.PannelMin_MouseHover);
            // 
            // PanelTitleText
            // 
            this.PanelTitleText.BackgroundImage = global::LiveWallpaperUI.Properties.Resources.title;
            this.PanelTitleText.Location = new System.Drawing.Point(0, 0);
            this.PanelTitleText.Name = "PanelTitleText";
            this.PanelTitleText.Size = new System.Drawing.Size(200, 34);
            this.PanelTitleText.TabIndex = 0;
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
            // PanelFrame
            // 
            this.PanelFrame.BackColor = System.Drawing.Color.White;
            this.PanelFrame.Controls.Add(this.ButtonClose);
            this.PanelFrame.Controls.Add(this.ButtonStart);
            this.PanelFrame.Controls.Add(this.GroupBoxFile);
            this.PanelFrame.Location = new System.Drawing.Point(64, 34);
            this.PanelFrame.Name = "PanelFrame";
            this.PanelFrame.Size = new System.Drawing.Size(896, 686);
            this.PanelFrame.TabIndex = 4;
            // 
            // ButtonClose
            // 
            this.ButtonClose.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ButtonClose.Location = new System.Drawing.Point(710, 651);
            this.ButtonClose.Name = "ButtonClose";
            this.ButtonClose.Size = new System.Drawing.Size(84, 23);
            this.ButtonClose.TabIndex = 2;
            this.ButtonClose.Text = "关闭(Close)";
            this.ButtonClose.UseVisualStyleBackColor = true;
            this.ButtonClose.Click += new System.EventHandler(this.ButtonClose_Click);
            // 
            // ButtonStart
            // 
            this.ButtonStart.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ButtonStart.Location = new System.Drawing.Point(800, 651);
            this.ButtonStart.Name = "ButtonStart";
            this.ButtonStart.Size = new System.Drawing.Size(84, 23);
            this.ButtonStart.TabIndex = 1;
            this.ButtonStart.Text = "开始(Start)";
            this.ButtonStart.UseVisualStyleBackColor = true;
            this.ButtonStart.Click += new System.EventHandler(this.ButtonStart_Click);
            // 
            // GroupBoxFile
            // 
            this.GroupBoxFile.Controls.Add(this.CheckBoxAudioNo);
            this.GroupBoxFile.Controls.Add(this.CheckBoxAudioYes);
            this.GroupBoxFile.Controls.Add(this.LabelPlaySound);
            this.GroupBoxFile.Controls.Add(this.NumberUpDownType);
            this.GroupBoxFile.Controls.Add(this.LabelShowFont);
            this.GroupBoxFile.Controls.Add(this.CheckBoxShowNo);
            this.GroupBoxFile.Controls.Add(this.CheckBoxShowYes);
            this.GroupBoxFile.Controls.Add(this.LabelShowFrame);
            this.GroupBoxFile.Controls.Add(this.CheckBoxShowMode5);
            this.GroupBoxFile.Controls.Add(this.CheckBoxShowMode4);
            this.GroupBoxFile.Controls.Add(this.CheckBoxShowMode3);
            this.GroupBoxFile.Controls.Add(this.CheckBoxShowMode2);
            this.GroupBoxFile.Controls.Add(this.CheckBoxShowMode1);
            this.GroupBoxFile.Controls.Add(this.LabelShowMode);
            this.GroupBoxFile.Controls.Add(this.CheckBoxDefault2);
            this.GroupBoxFile.Controls.Add(this.CheckBoxDefault1);
            this.GroupBoxFile.Controls.Add(this.LabelDefaultSelect);
            this.GroupBoxFile.Controls.Add(this.RadioButtonSelectMode);
            this.GroupBoxFile.Controls.Add(this.RadioButtonDefaultMode);
            this.GroupBoxFile.Controls.Add(this.LableMode);
            this.GroupBoxFile.Controls.Add(this.LabelTitleFilePath);
            this.GroupBoxFile.Controls.Add(this.TextBoxFilePath);
            this.GroupBoxFile.Controls.Add(this.ButtonOpen);
            this.GroupBoxFile.Controls.Add(this.LabelFilePath);
            this.GroupBoxFile.Location = new System.Drawing.Point(6, 6);
            this.GroupBoxFile.Name = "GroupBoxFile";
            this.GroupBoxFile.Size = new System.Drawing.Size(878, 320);
            this.GroupBoxFile.TabIndex = 0;
            this.GroupBoxFile.TabStop = false;
            // 
            // NumberUpDownType
            // 
            this.NumberUpDownType.Enabled = false;
            this.NumberUpDownType.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.NumberUpDownType.Location = new System.Drawing.Point(362, 193);
            this.NumberUpDownType.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.NumberUpDownType.Name = "NumberUpDownType";
            this.NumberUpDownType.Size = new System.Drawing.Size(120, 20);
            this.NumberUpDownType.TabIndex = 20;
            this.NumberUpDownType.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
            // 
            // LabelShowFont
            // 
            this.LabelShowFont.AutoSize = true;
            this.LabelShowFont.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LabelShowFont.Location = new System.Drawing.Point(34, 195);
            this.LabelShowFont.Name = "LabelShowFont";
            this.LabelShowFont.Size = new System.Drawing.Size(322, 13);
            this.LabelShowFont.TabIndex = 19;
            this.LabelShowFont.Text = "动态壁纸显示信息字体大小(Live Wallpaper Show Info Type):";
            // 
            // CheckBoxShowNo
            // 
            this.CheckBoxShowNo.AutoSize = true;
            this.CheckBoxShowNo.Checked = true;
            this.CheckBoxShowNo.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CheckBoxShowNo.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CheckBoxShowNo.Location = new System.Drawing.Point(508, 159);
            this.CheckBoxShowNo.Name = "CheckBoxShowNo";
            this.CheckBoxShowNo.Size = new System.Drawing.Size(62, 17);
            this.CheckBoxShowNo.TabIndex = 18;
            this.CheckBoxShowNo.Text = "不显示";
            this.CheckBoxShowNo.UseVisualStyleBackColor = true;
            this.CheckBoxShowNo.CheckedChanged += new System.EventHandler(this.CheckBoxShowNo_CheckedChanged);
            // 
            // CheckBoxShowYes
            // 
            this.CheckBoxShowYes.AutoSize = true;
            this.CheckBoxShowYes.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CheckBoxShowYes.Location = new System.Drawing.Point(452, 159);
            this.CheckBoxShowYes.Name = "CheckBoxShowYes";
            this.CheckBoxShowYes.Size = new System.Drawing.Size(50, 17);
            this.CheckBoxShowYes.TabIndex = 17;
            this.CheckBoxShowYes.Text = "显示";
            this.CheckBoxShowYes.UseVisualStyleBackColor = true;
            this.CheckBoxShowYes.CheckedChanged += new System.EventHandler(this.CheckBoxShowYes_CheckedChanged);
            // 
            // LabelShowFrame
            // 
            this.LabelShowFrame.AutoSize = true;
            this.LabelShowFrame.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LabelShowFrame.Location = new System.Drawing.Point(34, 160);
            this.LabelShowFrame.Name = "LabelShowFrame";
            this.LabelShowFrame.Size = new System.Drawing.Size(412, 13);
            this.LabelShowFrame.TabIndex = 16;
            this.LabelShowFrame.Text = "动态壁纸显示显卡型号和帧速率(Live Wallpaper Show Adapter & Frame Speed):";
            // 
            // CheckBoxShowMode5
            // 
            this.CheckBoxShowMode5.AutoSize = true;
            this.CheckBoxShowMode5.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CheckBoxShowMode5.Location = new System.Drawing.Point(639, 124);
            this.CheckBoxShowMode5.Name = "CheckBoxShowMode5";
            this.CheckBoxShowMode5.Size = new System.Drawing.Size(74, 17);
            this.CheckBoxShowMode5.TabIndex = 15;
            this.CheckBoxShowMode5.Text = "居中模式";
            this.CheckBoxShowMode5.UseVisualStyleBackColor = true;
            this.CheckBoxShowMode5.CheckedChanged += new System.EventHandler(this.CheckBoxShowMode5_CheckedChanged);
            // 
            // CheckBoxShowMode4
            // 
            this.CheckBoxShowMode4.AutoSize = true;
            this.CheckBoxShowMode4.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CheckBoxShowMode4.Location = new System.Drawing.Point(553, 124);
            this.CheckBoxShowMode4.Name = "CheckBoxShowMode4";
            this.CheckBoxShowMode4.Size = new System.Drawing.Size(74, 17);
            this.CheckBoxShowMode4.TabIndex = 14;
            this.CheckBoxShowMode4.Text = "平铺模式";
            this.CheckBoxShowMode4.UseVisualStyleBackColor = true;
            this.CheckBoxShowMode4.CheckedChanged += new System.EventHandler(this.CheckBoxShowMode4_CheckedChanged);
            // 
            // CheckBoxShowMode3
            // 
            this.CheckBoxShowMode3.AutoSize = true;
            this.CheckBoxShowMode3.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CheckBoxShowMode3.Location = new System.Drawing.Point(467, 124);
            this.CheckBoxShowMode3.Name = "CheckBoxShowMode3";
            this.CheckBoxShowMode3.Size = new System.Drawing.Size(74, 17);
            this.CheckBoxShowMode3.TabIndex = 13;
            this.CheckBoxShowMode3.Text = "拉伸模式";
            this.CheckBoxShowMode3.UseVisualStyleBackColor = true;
            this.CheckBoxShowMode3.CheckedChanged += new System.EventHandler(this.CheckBoxShowMode3_CheckedChanged);
            // 
            // CheckBoxShowMode2
            // 
            this.CheckBoxShowMode2.AutoSize = true;
            this.CheckBoxShowMode2.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CheckBoxShowMode2.Location = new System.Drawing.Point(381, 124);
            this.CheckBoxShowMode2.Name = "CheckBoxShowMode2";
            this.CheckBoxShowMode2.Size = new System.Drawing.Size(74, 17);
            this.CheckBoxShowMode2.TabIndex = 12;
            this.CheckBoxShowMode2.Text = "适应模式";
            this.CheckBoxShowMode2.UseVisualStyleBackColor = true;
            this.CheckBoxShowMode2.CheckedChanged += new System.EventHandler(this.CheckBoxShowMode2_CheckedChanged);
            // 
            // CheckBoxShowMode1
            // 
            this.CheckBoxShowMode1.AutoSize = true;
            this.CheckBoxShowMode1.Checked = true;
            this.CheckBoxShowMode1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CheckBoxShowMode1.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CheckBoxShowMode1.Location = new System.Drawing.Point(295, 124);
            this.CheckBoxShowMode1.Name = "CheckBoxShowMode1";
            this.CheckBoxShowMode1.Size = new System.Drawing.Size(74, 17);
            this.CheckBoxShowMode1.TabIndex = 11;
            this.CheckBoxShowMode1.Text = "填充模式";
            this.CheckBoxShowMode1.UseVisualStyleBackColor = true;
            this.CheckBoxShowMode1.CheckedChanged += new System.EventHandler(this.CheckBoxShowMode1_CheckedChanged);
            // 
            // LabelShowMode
            // 
            this.LabelShowMode.AutoSize = true;
            this.LabelShowMode.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LabelShowMode.Location = new System.Drawing.Point(34, 125);
            this.LabelShowMode.Name = "LabelShowMode";
            this.LabelShowMode.Size = new System.Drawing.Size(255, 13);
            this.LabelShowMode.TabIndex = 10;
            this.LabelShowMode.Text = "动态壁纸显示模式(Live Wallpaper Show Mode):";
            // 
            // CheckBoxDefault2
            // 
            this.CheckBoxDefault2.AutoSize = true;
            this.CheckBoxDefault2.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CheckBoxDefault2.Location = new System.Drawing.Point(374, 89);
            this.CheckBoxDefault2.Name = "CheckBoxDefault2";
            this.CheckBoxDefault2.Size = new System.Drawing.Size(80, 17);
            this.CheckBoxDefault2.TabIndex = 9;
            this.CheckBoxDefault2.Text = "示例壁纸2";
            this.CheckBoxDefault2.UseVisualStyleBackColor = true;
            this.CheckBoxDefault2.CheckedChanged += new System.EventHandler(this.CheckBoxDefault2_CheckedChanged);
            // 
            // CheckBoxDefault1
            // 
            this.CheckBoxDefault1.AutoSize = true;
            this.CheckBoxDefault1.Checked = true;
            this.CheckBoxDefault1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CheckBoxDefault1.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CheckBoxDefault1.Location = new System.Drawing.Point(288, 89);
            this.CheckBoxDefault1.Name = "CheckBoxDefault1";
            this.CheckBoxDefault1.Size = new System.Drawing.Size(80, 17);
            this.CheckBoxDefault1.TabIndex = 8;
            this.CheckBoxDefault1.Text = "示例壁纸1";
            this.CheckBoxDefault1.UseVisualStyleBackColor = true;
            this.CheckBoxDefault1.CheckedChanged += new System.EventHandler(this.CheckBoxDefault1_CheckedChanged);
            // 
            // LabelDefaultSelect
            // 
            this.LabelDefaultSelect.AutoSize = true;
            this.LabelDefaultSelect.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LabelDefaultSelect.Location = new System.Drawing.Point(34, 90);
            this.LabelDefaultSelect.Name = "LabelDefaultSelect";
            this.LabelDefaultSelect.Size = new System.Drawing.Size(248, 13);
            this.LabelDefaultSelect.TabIndex = 7;
            this.LabelDefaultSelect.Text = "动态壁纸默认视频选择(Live Wallpaper Mode):";
            // 
            // RadioButtonSelectMode
            // 
            this.RadioButtonSelectMode.AutoSize = true;
            this.RadioButtonSelectMode.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.RadioButtonSelectMode.Location = new System.Drawing.Point(319, 53);
            this.RadioButtonSelectMode.Name = "RadioButtonSelectMode";
            this.RadioButtonSelectMode.Size = new System.Drawing.Size(73, 17);
            this.RadioButtonSelectMode.TabIndex = 6;
            this.RadioButtonSelectMode.Text = "选择模式";
            this.RadioButtonSelectMode.UseVisualStyleBackColor = true;
            this.RadioButtonSelectMode.CheckedChanged += new System.EventHandler(this.RadioButtonSelectMode_CheckedChanged);
            // 
            // RadioButtonDefaultMode
            // 
            this.RadioButtonDefaultMode.AutoSize = true;
            this.RadioButtonDefaultMode.Checked = true;
            this.RadioButtonDefaultMode.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.RadioButtonDefaultMode.Location = new System.Drawing.Point(240, 53);
            this.RadioButtonDefaultMode.Name = "RadioButtonDefaultMode";
            this.RadioButtonDefaultMode.Size = new System.Drawing.Size(73, 17);
            this.RadioButtonDefaultMode.TabIndex = 5;
            this.RadioButtonDefaultMode.TabStop = true;
            this.RadioButtonDefaultMode.Text = "默认模式";
            this.RadioButtonDefaultMode.UseVisualStyleBackColor = true;
            this.RadioButtonDefaultMode.CheckedChanged += new System.EventHandler(this.RadioButtonDefaultMode_CheckedChanged);
            // 
            // LableMode
            // 
            this.LableMode.AutoSize = true;
            this.LableMode.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LableMode.Location = new System.Drawing.Point(34, 55);
            this.LableMode.Name = "LableMode";
            this.LableMode.Size = new System.Drawing.Size(200, 13);
            this.LableMode.TabIndex = 4;
            this.LableMode.Text = "动态壁纸模式(Live Wallpaper Mode):";
            // 
            // LabelTitleFilePath
            // 
            this.LabelTitleFilePath.AutoSize = true;
            this.LabelTitleFilePath.Font = new System.Drawing.Font("等线", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LabelTitleFilePath.Location = new System.Drawing.Point(6, 17);
            this.LabelTitleFilePath.Name = "LabelTitleFilePath";
            this.LabelTitleFilePath.Size = new System.Drawing.Size(244, 15);
            this.LabelTitleFilePath.TabIndex = 3;
            this.LabelTitleFilePath.Text = "动态壁纸模式(Live Wallpaper Mode)";
            // 
            // TextBoxFilePath
            // 
            this.TextBoxFilePath.Enabled = false;
            this.TextBoxFilePath.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.TextBoxFilePath.Location = new System.Drawing.Point(255, 262);
            this.TextBoxFilePath.Name = "TextBoxFilePath";
            this.TextBoxFilePath.ReadOnly = true;
            this.TextBoxFilePath.Size = new System.Drawing.Size(473, 20);
            this.TextBoxFilePath.TabIndex = 2;
            // 
            // ButtonOpen
            // 
            this.ButtonOpen.Enabled = false;
            this.ButtonOpen.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ButtonOpen.Location = new System.Drawing.Point(734, 260);
            this.ButtonOpen.Name = "ButtonOpen";
            this.ButtonOpen.Size = new System.Drawing.Size(78, 23);
            this.ButtonOpen.TabIndex = 1;
            this.ButtonOpen.Text = "选择(Select)";
            this.ButtonOpen.UseVisualStyleBackColor = true;
            this.ButtonOpen.Click += new System.EventHandler(this.ButtonOpen_Click);
            // 
            // LabelFilePath
            // 
            this.LabelFilePath.AutoSize = true;
            this.LabelFilePath.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LabelFilePath.Location = new System.Drawing.Point(34, 265);
            this.LabelFilePath.Name = "LabelFilePath";
            this.LabelFilePath.Size = new System.Drawing.Size(215, 13);
            this.LabelFilePath.TabIndex = 0;
            this.LabelFilePath.Text = "动态壁纸路径(Live Wallpaper File Path):";
            // 
            // LabelPlaySound
            // 
            this.LabelPlaySound.AutoSize = true;
            this.LabelPlaySound.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LabelPlaySound.Location = new System.Drawing.Point(34, 230);
            this.LabelPlaySound.Name = "LabelPlaySound";
            this.LabelPlaySound.Size = new System.Drawing.Size(251, 13);
            this.LabelPlaySound.TabIndex = 21;
            this.LabelPlaySound.Text = "动态壁纸播放音频(Live Wallpaper Play Audio):";
            // 
            // CheckBoxAudioNo
            // 
            this.CheckBoxAudioNo.AutoSize = true;
            this.CheckBoxAudioNo.Checked = true;
            this.CheckBoxAudioNo.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CheckBoxAudioNo.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CheckBoxAudioNo.Location = new System.Drawing.Point(347, 229);
            this.CheckBoxAudioNo.Name = "CheckBoxAudioNo";
            this.CheckBoxAudioNo.Size = new System.Drawing.Size(62, 17);
            this.CheckBoxAudioNo.TabIndex = 23;
            this.CheckBoxAudioNo.Text = "不播放";
            this.CheckBoxAudioNo.UseVisualStyleBackColor = true;
            this.CheckBoxAudioNo.CheckedChanged += new System.EventHandler(this.CheckBoxAudioNo_CheckedChanged);
            // 
            // CheckBoxAudioYes
            // 
            this.CheckBoxAudioYes.AutoSize = true;
            this.CheckBoxAudioYes.Font = new System.Drawing.Font("等线", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CheckBoxAudioYes.Location = new System.Drawing.Point(291, 229);
            this.CheckBoxAudioYes.Name = "CheckBoxAudioYes";
            this.CheckBoxAudioYes.Size = new System.Drawing.Size(50, 17);
            this.CheckBoxAudioYes.TabIndex = 22;
            this.CheckBoxAudioYes.Text = "播放";
            this.CheckBoxAudioYes.UseVisualStyleBackColor = true;
            this.CheckBoxAudioYes.CheckedChanged += new System.EventHandler(this.CheckBoxAudioYes_CheckedChanged);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(960, 720);
            this.Controls.Add(this.PanelFrame);
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
            this.PanelTitle.ResumeLayout(false);
            this.PanelFrame.ResumeLayout(false);
            this.GroupBoxFile.ResumeLayout(false);
            this.GroupBoxFile.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NumberUpDownType)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel PanelClose;
        private System.Windows.Forms.Panel PanelTool;
        private System.Windows.Forms.Panel PanelTitle;
        private System.Windows.Forms.Panel PanelIcon;
        private System.Windows.Forms.Panel PanelTitleText;
        private System.Windows.Forms.Panel PanelMin;
        private System.Windows.Forms.Panel PanelFrame;
        private System.Windows.Forms.GroupBox GroupBoxFile;
        private System.Windows.Forms.Button ButtonOpen;
        private System.Windows.Forms.Label LabelFilePath;
        private System.Windows.Forms.TextBox TextBoxFilePath;
        private System.Windows.Forms.Label LabelTitleFilePath;
        private System.Windows.Forms.RadioButton RadioButtonSelectMode;
        private System.Windows.Forms.RadioButton RadioButtonDefaultMode;
        private System.Windows.Forms.Label LableMode;
        private System.Windows.Forms.Label LabelDefaultSelect;
        private System.Windows.Forms.CheckBox CheckBoxDefault2;
        private System.Windows.Forms.CheckBox CheckBoxDefault1;
        private System.Windows.Forms.CheckBox CheckBoxShowMode5;
        private System.Windows.Forms.CheckBox CheckBoxShowMode4;
        private System.Windows.Forms.CheckBox CheckBoxShowMode3;
        private System.Windows.Forms.CheckBox CheckBoxShowMode2;
        private System.Windows.Forms.CheckBox CheckBoxShowMode1;
        private System.Windows.Forms.Label LabelShowMode;
        private System.Windows.Forms.NumericUpDown NumberUpDownType;
        private System.Windows.Forms.Label LabelShowFont;
        private System.Windows.Forms.CheckBox CheckBoxShowNo;
        private System.Windows.Forms.CheckBox CheckBoxShowYes;
        private System.Windows.Forms.Label LabelShowFrame;
        private System.Windows.Forms.Button ButtonClose;
        private System.Windows.Forms.Button ButtonStart;
        private System.Windows.Forms.Label LabelPlaySound;
        private System.Windows.Forms.CheckBox CheckBoxAudioNo;
        private System.Windows.Forms.CheckBox CheckBoxAudioYes;
    }
}

