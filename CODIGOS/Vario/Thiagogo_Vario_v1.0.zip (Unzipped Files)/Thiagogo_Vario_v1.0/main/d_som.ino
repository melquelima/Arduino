void play_welcome_beep()                 // Saudações de áudio
{
    for (int aa=100;aa<=800;aa=aa+100)
    {
        tone(tone_out1,aa,200);       
        tone(tone_out2,aa+3,200);
        delay(50);
    }
}
