Imports System.IO.Ports

Public Class Form1
    Dim conected As Boolean = False
    Dim index As Integer = 0

    Sub portas()
        ComboBox1.Items.Clear()
        ComboBox1.ResetText()
        For Each sp As String In My.Computer.Ports.SerialPortNames
            ComboBox1.Items.Add(sp)
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


    Private Sub Btn_GO_Click(sender As Object, e As EventArgs) Handles Btn_GO.Click
        If Txbx_pos.Text < 10 Then
            Txbx_pos.Text = "0" & Txbx_pos.Text
        End If

        SerialPort1.Write(Txbx_pos.Text & "!")

        'MsgBox(Txbx_pos.Text & "!")
        'SerialPort1.Write("!" & Txbx_pos.Text & "!")

    End Sub

    Private Sub Txbx_pos_TextChanged(sender As Object, e As EventArgs) Handles Txbx_pos.TextChanged
        If Txbx_pos.TextLength <> 0 Then
            If Not IsNumeric(Txbx_pos.Text.Substring(Txbx_pos.TextLength - 1, 1)) Then
                Txbx_pos.Text = ""
                MsgBox("digite apenas numeros inteiros")
            Else
                If Txbx_pos.Text > 25 Then
                    Txbx_pos.Text = ""
                    MsgBox("digite uma posição menor ou igual que 25")
                End If
            End If
        End If

    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        If Not conected Then
            portas()
        End If
    End Sub



    Private Sub ComboBox1_DropDown(sender As Object, e As EventArgs) Handles ComboBox1.DropDown
        Timer1.Enabled = False
    End Sub

    Private Sub ComboBox1_DropDownClosed(sender As Object, e As EventArgs) Handles ComboBox1.DropDownClosed
        Timer1.Enabled = True
    End Sub


    Private Sub ComboBox1_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox1.SelectedIndexChanged
        index = ComboBox1.SelectedIndex
    End Sub
End Class
