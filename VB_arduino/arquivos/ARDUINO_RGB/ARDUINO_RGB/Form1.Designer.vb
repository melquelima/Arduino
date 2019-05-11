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
        Me.TR = New System.Windows.Forms.TrackBar()
        Me.Conectar = New System.Windows.Forms.Button()
        Me.ComboBox1 = New System.Windows.Forms.ComboBox()
        Me.BtPortas = New System.Windows.Forms.Button()
        Me.LG = New System.Windows.Forms.Label()
        Me.LB = New System.Windows.Forms.Label()
        Me.LR = New System.Windows.Forms.Label()
        Me.TG = New System.Windows.Forms.TrackBar()
        Me.TB = New System.Windows.Forms.TrackBar()
        Me.SerialPort1 = New System.IO.Ports.SerialPort(Me.components)
        CType(Me.TR, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.TG, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.TB, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'TR
        '
        Me.TR.BackColor = System.Drawing.Color.Red
        Me.TR.Location = New System.Drawing.Point(12, 61)
        Me.TR.Maximum = 9
        Me.TR.Name = "TR"
        Me.TR.Size = New System.Drawing.Size(330, 45)
        Me.TR.TabIndex = 1
        '
        'Conectar
        '
        Me.Conectar.Location = New System.Drawing.Point(212, 11)
        Me.Conectar.Name = "Conectar"
        Me.Conectar.Size = New System.Drawing.Size(82, 24)
        Me.Conectar.TabIndex = 16
        Me.Conectar.Text = "Conectar"
        Me.Conectar.UseVisualStyleBackColor = True
        '
        'ComboBox1
        '
        Me.ComboBox1.FormattingEnabled = True
        Me.ComboBox1.Location = New System.Drawing.Point(30, 12)
        Me.ComboBox1.Name = "ComboBox1"
        Me.ComboBox1.Size = New System.Drawing.Size(85, 21)
        Me.ComboBox1.TabIndex = 15
        '
        'BtPortas
        '
        Me.BtPortas.Location = New System.Drawing.Point(131, 9)
        Me.BtPortas.Name = "BtPortas"
        Me.BtPortas.Size = New System.Drawing.Size(72, 26)
        Me.BtPortas.TabIndex = 14
        Me.BtPortas.Text = "Portas"
        Me.BtPortas.UseVisualStyleBackColor = True
        '
        'LG
        '
        Me.LG.AutoSize = True
        Me.LG.Font = New System.Drawing.Font("Microsoft Sans Serif", 15.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.LG.Location = New System.Drawing.Point(348, 120)
        Me.LG.Name = "LG"
        Me.LG.Size = New System.Drawing.Size(25, 25)
        Me.LG.TabIndex = 13
        Me.LG.Text = "0"
        '
        'LB
        '
        Me.LB.AutoSize = True
        Me.LB.Font = New System.Drawing.Font("Microsoft Sans Serif", 15.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.LB.Location = New System.Drawing.Point(348, 172)
        Me.LB.Name = "LB"
        Me.LB.Size = New System.Drawing.Size(25, 25)
        Me.LB.TabIndex = 12
        Me.LB.Text = "0"
        '
        'LR
        '
        Me.LR.AutoSize = True
        Me.LR.Font = New System.Drawing.Font("Microsoft Sans Serif", 15.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.LR.Location = New System.Drawing.Point(348, 71)
        Me.LR.Name = "LR"
        Me.LR.Size = New System.Drawing.Size(25, 25)
        Me.LR.TabIndex = 11
        Me.LR.Text = "0"
        '
        'TG
        '
        Me.TG.BackColor = System.Drawing.Color.Green
        Me.TG.Location = New System.Drawing.Point(12, 111)
        Me.TG.Maximum = 9
        Me.TG.Name = "TG"
        Me.TG.Size = New System.Drawing.Size(330, 45)
        Me.TG.TabIndex = 10
        '
        'TB
        '
        Me.TB.BackColor = System.Drawing.Color.Blue
        Me.TB.Location = New System.Drawing.Point(12, 162)
        Me.TB.Maximum = 9
        Me.TB.Name = "TB"
        Me.TB.Size = New System.Drawing.Size(330, 45)
        Me.TB.TabIndex = 9
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(385, 223)
        Me.Controls.Add(Me.Conectar)
        Me.Controls.Add(Me.ComboBox1)
        Me.Controls.Add(Me.BtPortas)
        Me.Controls.Add(Me.LG)
        Me.Controls.Add(Me.LB)
        Me.Controls.Add(Me.LR)
        Me.Controls.Add(Me.TG)
        Me.Controls.Add(Me.TB)
        Me.Controls.Add(Me.TR)
        Me.Name = "Form1"
        Me.Text = "Form1"
        CType(Me.TR, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.TG, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.TB, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents TR As System.Windows.Forms.TrackBar
    Friend WithEvents Conectar As System.Windows.Forms.Button
    Friend WithEvents ComboBox1 As System.Windows.Forms.ComboBox
    Friend WithEvents BtPortas As System.Windows.Forms.Button
    Friend WithEvents LG As System.Windows.Forms.Label
    Friend WithEvents LB As System.Windows.Forms.Label
    Friend WithEvents LR As System.Windows.Forms.Label
    Friend WithEvents TG As System.Windows.Forms.TrackBar
    Friend WithEvents TB As System.Windows.Forms.TrackBar
    Friend WithEvents SerialPort1 As System.IO.Ports.SerialPort

End Class
