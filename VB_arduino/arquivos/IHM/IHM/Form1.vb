Imports System.IO.Ports

Public Class Form1
    Dim conected As Boolean = False
    Dim index As Integer = 0
    Dim porta(10) As String

    Sub portas()
        ComboBox1.Items.Clear()
        ComboBox1.ResetText()
        For Each sp As String In porta
            If sp <> "" Then
                ComboBox1.Items.Add(sp)
            End If
        Next

        If ComboBox1.Items.Count <> 0 Then
            Try
                ComboBox1.SelectedIndex = index
            Catch ex As Exception
                index = 0
                ComboBox1.SelectedIndex = index
            End Try
        End If

    End Sub


    Private Sub BT_CONECTAR_Click(sender As Object, e As EventArgs) Handles BT_CONECTAR.Click
        If BT_CONECTAR.Text = "CONECTAR" Then
            If ComboBox1.Items.Count <> 0 Then
                Try
                    SerialPort1.Close()
                    SerialPort1.PortName = ComboBox1.SelectedItem.ToString
                    SerialPort1.BaudRate = 9600
                    SerialPort1.DataBits = 8
                    SerialPort1.Parity = Parity.None
                    SerialPort1.StopBits = StopBits.One
                    SerialPort1.Handshake = Handshake.None
                    SerialPort1.Encoding = System.Text.Encoding.Default
                    SerialPort1.ReadTimeout = 1000

                    SerialPort1.Open()

                    BT_CONECTAR.Text = "DESCONECTAR"
                    GroupBox2.Enabled = True
                    conected = True
                Catch ex As Exception
                    MsgBox(ex.Message.ToString)
                End Try

            Else
                MsgBox("Não há portas disponíveis")
            End If
        Else
            SerialPort1.Close()
            BT_CONECTAR.Text = "CONECTAR"
            GroupBox2.Enabled = False
            conected = False
        End If
    End Sub




    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        For i = 1 To 9
            porta(i) = ""
        Next i

        Dim x As Integer
        x = 1
        If Not conected Then
            For Each sp As String In My.Computer.Ports.SerialPortNames
                porta(x) = sp
                x = x + 1
            Next sp

        End If
    End Sub



    Private Sub ComboBox1_DropDown(sender As Object, e As EventArgs) Handles ComboBox1.DropDown
        Timer1.Enabled = False
        portas()
    End Sub

    Private Sub ComboBox1_DropDownClosed(sender As Object, e As EventArgs) Handles ComboBox1.DropDownClosed
        Timer1.Enabled = True
    End Sub


    Private Sub ComboBox1_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox1.SelectedIndexChanged
        index = ComboBox1.SelectedIndex
    End Sub


    Private Sub R120_CheckedChanged(sender As Object, e As EventArgs) Handles R120.CheckedChanged
        If R120.Checked Then
            If conected Then
                SerialPort1.Write("f")
            Else
                MsgBox("conecte antes de configurar")
            End If
        End If
    End Sub

    Private Sub R180_CheckedChanged(sender As Object, e As EventArgs) Handles R180.CheckedChanged
        If R180.Checked Then
            If conected Then
                SerialPort1.Write("g")
            Else
                MsgBox("conecte antes de configurar")
            End If
        End If
    End Sub

    Private Sub R240_CheckedChanged(sender As Object, e As EventArgs) Handles R240.CheckedChanged
        If R240.Checked Then
            If conected Then
                SerialPort1.Write("h")
            Else
                MsgBox("conecte antes de configurar")
            End If
        End If
    End Sub

    Private Sub R300_CheckedChanged(sender As Object, e As EventArgs) Handles R300.CheckedChanged
        If R300.Checked Then
            If conected Then
                SerialPort1.Write("i")
            Else
                MsgBox("conecte antes de configurar")
            End If
        End If
    End Sub

    Private Sub R360_CheckedChanged(sender As Object, e As EventArgs) Handles R360.CheckedChanged
        If R360.Checked Then
            If conected Then
                SerialPort1.Write("j")
            Else
                MsgBox("conecte antes de configurar")
            End If
        End If
    End Sub

    Private Sub Btn_esq_Click(sender As Object, e As EventArgs) Handles Btn_esq.Click
        SerialPort1.Write("e")
    End Sub

    Private Sub Btn_dir_Click(sender As Object, e As EventArgs) Handles Btn_dir.Click
        SerialPort1.Write("d")
    End Sub


    Private Sub Btn_rele_Click(sender As Object, e As EventArgs) Handles Btn_rele.Click
        SerialPort1.Write("r")
    End Sub
End Class
