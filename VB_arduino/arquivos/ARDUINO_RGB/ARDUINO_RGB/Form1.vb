Imports System.IO.Ports

Public Class Form1
    Dim letras() As Char = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "{", "|", "}", "~"}

    Private Sub TR_Scroll(sender As Object, e As EventArgs) Handles TR.Scroll 'barra Red
        LR.Text = TR.Value 'Label Red
        If Conectar.Text = "Desconectar" Then ' botao conectar
            SerialPort1.Write(letras(TR.Value))
        End If

    End Sub

    Private Sub TG_Scroll(sender As Object, e As EventArgs) Handles TG.Scroll
        LG.Text = TG.Value + 10
        If Conectar.Text = "Desconectar" Then
            SerialPort1.Write(letras(TG.Value + 10))
        End If
    End Sub

    Private Sub TB_Scroll(sender As Object, e As EventArgs) Handles TB.Scroll
        LB.Text = TB.Value + 20
        If Conectar.Text = "Desconectar" Then
            SerialPort1.Write(letras(TB.Value + 20))
        End If
    End Sub


    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles Me.Load
        portas()
    End Sub

    Sub portas()
        ComboBox1.Items.Clear()
        ComboBox1.ResetText()
        For Each sp As String In My.Computer.Ports.SerialPortNames
            ComboBox1.Items.Add(sp)
        Next

        If ComboBox1.Items.Count <> 0 Then
            ComboBox1.SelectedIndex = 0
        End If

    End Sub

    Private Sub BtPortas_Click(sender As Object, e As EventArgs) Handles BtPortas.Click
        portas()
    End Sub

    Private Sub Conectar_Click(sender As Object, e As EventArgs) Handles Conectar.Click
        If Conectar.Text = "Conectar" Then
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

                    Conectar.Text = "Desconectar"
                Catch ex As Exception
                    MsgBox(ex.Message.ToString)
                End Try

            Else
                MsgBox("Não há portas disponíveis")
            End If

        End If
    End Sub
End Class
