<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ComboBox1 = New System.Windows.Forms.ComboBox()
        Me.BT_CONECTAR = New System.Windows.Forms.Button()
        Me.SerialPort1 = New System.IO.Ports.SerialPort(Me.components)
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.GroupBox2 = New System.Windows.Forms.GroupBox()
        Me.Btn_rele = New System.Windows.Forms.Button()
        Me.Btn_dir = New System.Windows.Forms.Button()
        Me.Btn_esq = New System.Windows.Forms.Button()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.GroupBox3 = New System.Windows.Forms.GroupBox()
        Me.R360 = New System.Windows.Forms.RadioButton()
        Me.R300 = New System.Windows.Forms.RadioButton()
        Me.R240 = New System.Windows.Forms.RadioButton()
        Me.R180 = New System.Windows.Forms.RadioButton()
        Me.R120 = New System.Windows.Forms.RadioButton()
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.GroupBox3.SuspendLayout()
        Me.SuspendLayout()
        '
        'ComboBox1
        '
        Me.ComboBox1.FormattingEnabled = True
        Me.ComboBox1.Location = New System.Drawing.Point(6, 21)
        Me.ComboBox1.Name = "ComboBox1"
        Me.ComboBox1.Size = New System.Drawing.Size(74, 21)
        Me.ComboBox1.TabIndex = 0
        '
        'BT_CONECTAR
        '
        Me.BT_CONECTAR.Location = New System.Drawing.Point(88, 19)
        Me.BT_CONECTAR.Name = "BT_CONECTAR"
        Me.BT_CONECTAR.Size = New System.Drawing.Size(190, 23)
        Me.BT_CONECTAR.TabIndex = 2
        Me.BT_CONECTAR.Text = "CONECTAR"
        Me.BT_CONECTAR.UseVisualStyleBackColor = True
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.ComboBox1)
        Me.GroupBox1.Controls.Add(Me.BT_CONECTAR)
        Me.GroupBox1.Location = New System.Drawing.Point(3, 12)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(429, 59)
        Me.GroupBox1.TabIndex = 3
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Conectar"
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.Btn_rele)
        Me.GroupBox2.Controls.Add(Me.Btn_dir)
        Me.GroupBox2.Controls.Add(Me.Btn_esq)
        Me.GroupBox2.Enabled = False
        Me.GroupBox2.Location = New System.Drawing.Point(3, 120)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(421, 49)
        Me.GroupBox2.TabIndex = 4
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Controle"
        '
        'Btn_rele
        '
        Me.Btn_rele.Location = New System.Drawing.Point(216, 13)
        Me.Btn_rele.Name = "Btn_rele"
        Me.Btn_rele.Size = New System.Drawing.Size(75, 23)
        Me.Btn_rele.TabIndex = 6
        Me.Btn_rele.Text = "Rele"
        Me.Btn_rele.UseVisualStyleBackColor = True
        '
        'Btn_dir
        '
        Me.Btn_dir.Location = New System.Drawing.Point(123, 13)
        Me.Btn_dir.Name = "Btn_dir"
        Me.Btn_dir.Size = New System.Drawing.Size(75, 23)
        Me.Btn_dir.TabIndex = 5
        Me.Btn_dir.Text = "==>"
        Me.Btn_dir.UseVisualStyleBackColor = True
        '
        'Btn_esq
        '
        Me.Btn_esq.Location = New System.Drawing.Point(42, 13)
        Me.Btn_esq.Name = "Btn_esq"
        Me.Btn_esq.Size = New System.Drawing.Size(75, 23)
        Me.Btn_esq.TabIndex = 2
        Me.Btn_esq.Text = "<=="
        Me.Btn_esq.UseVisualStyleBackColor = True
        '
        'Timer1
        '
        Me.Timer1.Enabled = True
        '
        'GroupBox3
        '
        Me.GroupBox3.Controls.Add(Me.R360)
        Me.GroupBox3.Controls.Add(Me.R300)
        Me.GroupBox3.Controls.Add(Me.R240)
        Me.GroupBox3.Controls.Add(Me.R180)
        Me.GroupBox3.Controls.Add(Me.R120)
        Me.GroupBox3.Location = New System.Drawing.Point(10, 74)
        Me.GroupBox3.Name = "GroupBox3"
        Me.GroupBox3.Size = New System.Drawing.Size(413, 46)
        Me.GroupBox3.TabIndex = 5
        Me.GroupBox3.TabStop = False
        Me.GroupBox3.Text = "Configurar ângulo"
        '
        'R360
        '
        Me.R360.AutoSize = True
        Me.R360.Location = New System.Drawing.Point(224, 23)
        Me.R360.Name = "R360"
        Me.R360.Size = New System.Drawing.Size(47, 17)
        Me.R360.TabIndex = 4
        Me.R360.TabStop = True
        Me.R360.Text = "360º"
        Me.R360.UseVisualStyleBackColor = True
        '
        'R300
        '
        Me.R300.AutoSize = True
        Me.R300.Location = New System.Drawing.Point(177, 23)
        Me.R300.Name = "R300"
        Me.R300.Size = New System.Drawing.Size(47, 17)
        Me.R300.TabIndex = 3
        Me.R300.TabStop = True
        Me.R300.Text = "300º"
        Me.R300.UseVisualStyleBackColor = True
        '
        'R240
        '
        Me.R240.AutoSize = True
        Me.R240.Location = New System.Drawing.Point(120, 23)
        Me.R240.Name = "R240"
        Me.R240.Size = New System.Drawing.Size(47, 17)
        Me.R240.TabIndex = 2
        Me.R240.TabStop = True
        Me.R240.Text = "240º"
        Me.R240.UseVisualStyleBackColor = True
        '
        'R180
        '
        Me.R180.AutoSize = True
        Me.R180.Location = New System.Drawing.Point(63, 23)
        Me.R180.Name = "R180"
        Me.R180.Size = New System.Drawing.Size(47, 17)
        Me.R180.TabIndex = 1
        Me.R180.TabStop = True
        Me.R180.Text = "180º"
        Me.R180.UseVisualStyleBackColor = True
        '
        'R120
        '
        Me.R120.AutoSize = True
        Me.R120.Location = New System.Drawing.Point(6, 23)
        Me.R120.Name = "R120"
        Me.R120.Size = New System.Drawing.Size(47, 17)
        Me.R120.TabIndex = 0
        Me.R120.TabStop = True
        Me.R120.Text = "120º"
        Me.R120.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(301, 181)
        Me.Controls.Add(Me.GroupBox3)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.GroupBox1)
        Me.Name = "Form1"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Form1"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox3.ResumeLayout(False)
        Me.GroupBox3.PerformLayout()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents ComboBox1 As System.Windows.Forms.ComboBox
    Friend WithEvents BT_CONECTAR As System.Windows.Forms.Button
    Friend WithEvents SerialPort1 As System.IO.Ports.SerialPort
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents Btn_esq As System.Windows.Forms.Button
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents Btn_dir As System.Windows.Forms.Button
    Friend WithEvents GroupBox3 As System.Windows.Forms.GroupBox
    Friend WithEvents R360 As System.Windows.Forms.RadioButton
    Friend WithEvents R300 As System.Windows.Forms.RadioButton
    Friend WithEvents R240 As System.Windows.Forms.RadioButton
    Friend WithEvents R180 As System.Windows.Forms.RadioButton
    Friend WithEvents R120 As System.Windows.Forms.RadioButton
    Friend WithEvents Btn_rele As System.Windows.Forms.Button

End Class
