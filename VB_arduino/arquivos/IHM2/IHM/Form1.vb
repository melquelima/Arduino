Imports System.IO.Ports

Public Class Form1
    Dim conected As Boolean = False
    Dim index As Integer = 0

    Sub portas()
        '  Me.Size = New Size(303, 210)

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

    Private Sub Btn_GO_Click(sender As Object, e As EventArgs) Handles Btn_GO.Click

        SerialPort1.Write("L")
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        SerialPort1.Write("D")
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        SerialPort1.Write("R")
    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        SerialPort1.Write("5")
    End Sub


    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        SerialPort1.Write("1")
    End Sub

    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        SerialPort1.Write("2")
    End Sub
End Class
