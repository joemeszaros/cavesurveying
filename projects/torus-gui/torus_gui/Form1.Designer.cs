namespace torus_gui
{
    partial class mainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(mainForm));
            this.mainMenu = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.meshToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.renderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.status = new System.Windows.Forms.StatusStrip();
            this.tools = new System.Windows.Forms.ToolStrip();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.panel1 = new System.Windows.Forms.Panel();
            this.process1 = new System.Diagnostics.Process();
            this.panel2 = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.button1 = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton9 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton8 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton7 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton6 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton5 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton4 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton3 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton11 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton10 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton13 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton12 = new System.Windows.Forms.ToolStripButton();
            this.mainMenu.SuspendLayout();
            this.status.SuspendLayout();
            this.tools.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // mainMenu
            // 
            this.mainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editToolStripMenuItem,
            this.meshToolStripMenuItem,
            this.renderToolStripMenuItem,
            this.viewToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.mainMenu.Location = new System.Drawing.Point(0, 0);
            this.mainMenu.Name = "mainMenu";
            this.mainMenu.Size = new System.Drawing.Size(929, 24);
            this.mainMenu.TabIndex = 0;
            this.mainMenu.Text = "mainMenu";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
            this.editToolStripMenuItem.Text = "Edit";
            // 
            // meshToolStripMenuItem
            // 
            this.meshToolStripMenuItem.Name = "meshToolStripMenuItem";
            this.meshToolStripMenuItem.Size = new System.Drawing.Size(48, 20);
            this.meshToolStripMenuItem.Text = "Mesh";
            // 
            // renderToolStripMenuItem
            // 
            this.renderToolStripMenuItem.Name = "renderToolStripMenuItem";
            this.renderToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            this.renderToolStripMenuItem.Text = "Render";
            // 
            // viewToolStripMenuItem
            // 
            this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
            this.viewToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.viewToolStripMenuItem.Text = "View";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // status
            // 
            this.status.BackColor = System.Drawing.Color.Silver;
            this.status.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.status.Location = new System.Drawing.Point(0, 264);
            this.status.Name = "status";
            this.status.Size = new System.Drawing.Size(929, 22);
            this.status.TabIndex = 1;
            this.status.Text = "File : d:\\cave\\vadvizek.xml";
            this.status.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.status_ItemClicked);
            // 
            // tools
            // 
            this.tools.AutoSize = false;
            this.tools.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(240)))), ((int)(((byte)(240)))), ((int)(((byte)(240)))));
            this.tools.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.tools.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton2,
            this.toolStripButton9,
            this.toolStripButton8,
            this.toolStripButton7,
            this.toolStripSeparator1,
            this.toolStripButton6,
            this.toolStripButton5,
            this.toolStripButton4,
            this.toolStripButton3,
            this.toolStripSeparator2,
            this.toolStripButton11,
            this.toolStripButton10,
            this.toolStripButton13,
            this.toolStripSeparator3,
            this.toolStripButton12});
            this.tools.Location = new System.Drawing.Point(0, 24);
            this.tools.Name = "tools";
            this.tools.Size = new System.Drawing.Size(929, 43);
            this.tools.TabIndex = 2;
            this.tools.Text = "toolStrip1";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 43);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 43);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 43);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.DimGray;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.button1);
            this.panel1.Controls.Add(this.pictureBox1);
            this.panel1.Controls.Add(this.label9);
            this.panel1.Controls.Add(this.label8);
            this.panel1.Controls.Add(this.label7);
            this.panel1.Controls.Add(this.label6);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel1.Location = new System.Drawing.Point(0, 187);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(929, 77);
            this.panel1.TabIndex = 3;
            // 
            // process1
            // 
            this.process1.StartInfo.Domain = "";
            this.process1.StartInfo.LoadUserProfile = false;
            this.process1.StartInfo.Password = null;
            this.process1.StartInfo.StandardErrorEncoding = null;
            this.process1.StartInfo.StandardOutputEncoding = null;
            this.process1.StartInfo.UserName = "";
            this.process1.SynchronizingObject = this;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.FloralWhite;
            this.panel2.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel2.Location = new System.Drawing.Point(0, 183);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(929, 4);
            this.panel2.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label1.Location = new System.Drawing.Point(143, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(119, 25);
            this.label1.TabIndex = 0;
            this.label1.Text = "Vadvizek-útja";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label2.Location = new System.Drawing.Point(407, 11);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(112, 20);
            this.label2.TabIndex = 1;
            this.label2.Text = "Date : 2011.10.03";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Arial Narrow", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label3.Location = new System.Drawing.Point(145, 39);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(135, 16);
            this.label3.TabIndex = 2;
            this.label3.Text = "Cadastral number : 5230-1";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Arial Narrow", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label4.Location = new System.Drawing.Point(145, 55);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(100, 16);
            this.label4.TabIndex = 3;
            this.label4.Text = "Location : Budapest";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label5.Location = new System.Drawing.Point(407, 31);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(176, 20);
            this.label5.TabIndex = 4;
            this.label5.Text = "Reporter : Mészáros József";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label6.Location = new System.Drawing.Point(407, 51);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(247, 20);
            this.label6.TabIndex = 5;
            this.label6.Text = "Members : Ács Réka, Mészáros József";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label7.Location = new System.Drawing.Point(730, 11);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(98, 20);
            this.label7.TabIndex = 6;
            this.label7.Text = "Vertices : 1456";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label8.Location = new System.Drawing.Point(730, 31);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(86, 20);
            this.label8.TabIndex = 7;
            this.label8.Text = "Faces : 1414";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label9.Location = new System.Drawing.Point(730, 51);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(96, 20);
            this.label9.TabIndex = 8;
            this.label9.Text = "Segments : 20";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.BackColor = System.Drawing.Color.Silver;
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(145, 17);
            this.toolStripStatusLabel1.Text = "File : d:\\cave\\vadvizek.xml";
            this.toolStripStatusLabel1.Click += new System.EventHandler(this.toolStripStatusLabel1_Click);
            // 
            // button1
            // 
            this.button1.Image = global::torus_gui.Properties.Resources.down_small;
            this.button1.Location = new System.Drawing.Point(873, 1);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(52, 48);
            this.button1.TabIndex = 10;
            this.button1.UseVisualStyleBackColor = true;
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackgroundImage = global::torus_gui.Properties.Resources.torus2;
            this.pictureBox1.Location = new System.Drawing.Point(11, 3);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(116, 73);
            this.pictureBox1.TabIndex = 9;
            this.pictureBox1.TabStop = false;
            // 
            // toolStripButton2
            // 
            this.toolStripButton2.AutoSize = false;
            this.toolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton2.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton2.Image")));
            this.toolStripButton2.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.toolStripButton2.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton2.Margin = new System.Windows.Forms.Padding(0);
            this.toolStripButton2.Name = "toolStripButton2";
            this.toolStripButton2.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.toolStripButton2.Size = new System.Drawing.Size(40, 40);
            // 
            // toolStripButton9
            // 
            this.toolStripButton9.AutoSize = false;
            this.toolStripButton9.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton9.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton9.Image")));
            this.toolStripButton9.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.toolStripButton9.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton9.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton9.Margin = new System.Windows.Forms.Padding(0);
            this.toolStripButton9.Name = "toolStripButton9";
            this.toolStripButton9.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.toolStripButton9.Size = new System.Drawing.Size(40, 40);
            // 
            // toolStripButton8
            // 
            this.toolStripButton8.AutoSize = false;
            this.toolStripButton8.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton8.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton8.Image")));
            this.toolStripButton8.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.toolStripButton8.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton8.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton8.Margin = new System.Windows.Forms.Padding(0);
            this.toolStripButton8.Name = "toolStripButton8";
            this.toolStripButton8.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.toolStripButton8.Size = new System.Drawing.Size(40, 40);
            // 
            // toolStripButton7
            // 
            this.toolStripButton7.AutoSize = false;
            this.toolStripButton7.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton7.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton7.Image")));
            this.toolStripButton7.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.toolStripButton7.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton7.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton7.Margin = new System.Windows.Forms.Padding(0);
            this.toolStripButton7.Name = "toolStripButton7";
            this.toolStripButton7.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.toolStripButton7.Size = new System.Drawing.Size(40, 40);
            // 
            // toolStripButton6
            // 
            this.toolStripButton6.AutoSize = false;
            this.toolStripButton6.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton6.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton6.Image")));
            this.toolStripButton6.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.toolStripButton6.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton6.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton6.Margin = new System.Windows.Forms.Padding(0);
            this.toolStripButton6.Name = "toolStripButton6";
            this.toolStripButton6.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.toolStripButton6.Size = new System.Drawing.Size(40, 40);
            // 
            // toolStripButton5
            // 
            this.toolStripButton5.AutoSize = false;
            this.toolStripButton5.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton5.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton5.Image")));
            this.toolStripButton5.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.toolStripButton5.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton5.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton5.Margin = new System.Windows.Forms.Padding(0);
            this.toolStripButton5.Name = "toolStripButton5";
            this.toolStripButton5.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.toolStripButton5.Size = new System.Drawing.Size(40, 40);
            // 
            // toolStripButton4
            // 
            this.toolStripButton4.AutoSize = false;
            this.toolStripButton4.Checked = true;
            this.toolStripButton4.CheckState = System.Windows.Forms.CheckState.Checked;
            this.toolStripButton4.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton4.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton4.Image")));
            this.toolStripButton4.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.toolStripButton4.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton4.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton4.Margin = new System.Windows.Forms.Padding(0);
            this.toolStripButton4.Name = "toolStripButton4";
            this.toolStripButton4.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.toolStripButton4.Size = new System.Drawing.Size(40, 40);
            // 
            // toolStripButton3
            // 
            this.toolStripButton3.AutoSize = false;
            this.toolStripButton3.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton3.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton3.Image")));
            this.toolStripButton3.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.toolStripButton3.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton3.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton3.Margin = new System.Windows.Forms.Padding(0);
            this.toolStripButton3.Name = "toolStripButton3";
            this.toolStripButton3.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.toolStripButton3.Size = new System.Drawing.Size(40, 40);
            // 
            // toolStripButton11
            // 
            this.toolStripButton11.AutoSize = false;
            this.toolStripButton11.Checked = true;
            this.toolStripButton11.CheckState = System.Windows.Forms.CheckState.Checked;
            this.toolStripButton11.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton11.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton11.Image")));
            this.toolStripButton11.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.toolStripButton11.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton11.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton11.Margin = new System.Windows.Forms.Padding(0);
            this.toolStripButton11.Name = "toolStripButton11";
            this.toolStripButton11.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.toolStripButton11.Size = new System.Drawing.Size(40, 40);
            // 
            // toolStripButton10
            // 
            this.toolStripButton10.AutoSize = false;
            this.toolStripButton10.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton10.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton10.Image")));
            this.toolStripButton10.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.toolStripButton10.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton10.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton10.Margin = new System.Windows.Forms.Padding(0);
            this.toolStripButton10.Name = "toolStripButton10";
            this.toolStripButton10.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.toolStripButton10.Size = new System.Drawing.Size(40, 40);
            // 
            // toolStripButton13
            // 
            this.toolStripButton13.AutoSize = false;
            this.toolStripButton13.Checked = true;
            this.toolStripButton13.CheckState = System.Windows.Forms.CheckState.Checked;
            this.toolStripButton13.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton13.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton13.Image")));
            this.toolStripButton13.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.toolStripButton13.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton13.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton13.Margin = new System.Windows.Forms.Padding(0);
            this.toolStripButton13.Name = "toolStripButton13";
            this.toolStripButton13.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.toolStripButton13.Size = new System.Drawing.Size(40, 40);
            // 
            // toolStripButton12
            // 
            this.toolStripButton12.AutoSize = false;
            this.toolStripButton12.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton12.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton12.Image")));
            this.toolStripButton12.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.toolStripButton12.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton12.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton12.Margin = new System.Windows.Forms.Padding(0);
            this.toolStripButton12.Name = "toolStripButton12";
            this.toolStripButton12.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.toolStripButton12.Size = new System.Drawing.Size(40, 40);
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(86)))), ((int)(((byte)(86)))), ((int)(((byte)(86)))));
            this.ClientSize = new System.Drawing.Size(929, 286);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.tools);
            this.Controls.Add(this.status);
            this.Controls.Add(this.mainMenu);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.mainMenu;
            this.Name = "mainForm";
            this.Text = "Torus - 3D cave surveying";
            this.mainMenu.ResumeLayout(false);
            this.mainMenu.PerformLayout();
            this.status.ResumeLayout(false);
            this.status.PerformLayout();
            this.tools.ResumeLayout(false);
            this.tools.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip mainMenu;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem meshToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem renderToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem viewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.StatusStrip status;
        private System.Windows.Forms.ToolStrip tools;
        private System.Windows.Forms.ToolStripButton toolStripButton2;
        private System.Windows.Forms.ToolStripButton toolStripButton9;
        private System.Windows.Forms.ToolStripButton toolStripButton8;
        private System.Windows.Forms.ToolStripButton toolStripButton7;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton toolStripButton6;
        private System.Windows.Forms.ToolStripButton toolStripButton5;
        private System.Windows.Forms.ToolStripButton toolStripButton4;
        private System.Windows.Forms.ToolStripButton toolStripButton3;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton toolStripButton11;
        private System.Windows.Forms.ToolStripButton toolStripButton10;
        private System.Windows.Forms.ToolStripButton toolStripButton13;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripButton toolStripButton12;
        private System.Windows.Forms.Panel panel1;
        private System.Diagnostics.Process process1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.Button button1;
    }
}

