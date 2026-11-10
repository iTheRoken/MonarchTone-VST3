# MonarchTone — VST3 de voces cinematográficas suaves

Plugin VST3 **original e independiente** creado para acercarse a la *textura de postproducción* que se escucha en la referencia aportada por el usuario. No es un clon de una voz, ni incluye modelos TTS, música, muestras de sonido de terceros o material del creador del video. No garantiza reproducir el timbre de los intérpretes.

## Qué hace

- **Voice Character**: Warm Narrator (más limpio); Pixel Dialogue (apagado/digital); Ethereal Room (más ambiente).
- **Digital Age**: filtro de agudos y textura digital suave.
- **Body**: realza cuerpo grave-medio sin cambiar pitch.
- **Texture**: saturación suave.
- **Room**: reflexiones ambiente.
- **Echo**: repeticiones discretas.
- **Flutter**: sutil inestabilidad electrónica.
- **Dry / Wet**: mezcla de señal limpia y procesada.
- **Output dB**: volumen de salida.

### Recomendaciones de partida (voz hablada limpia)
- Narrador tipo «Félix»: Warm Narrator; Digital Age 20; Body 35; Texture 5; Room 10; Echo 0; Flutter 0; Mix 80.
- Voz serena tipo «Jesús»: Pixel Dialogue; Digital Age 25; Body 55; Texture 7; Room 23; Echo 8; Flutter 4; Mix 90.
- Más etéreo: Ethereal Room; Digital Age 35; Body 50; Texture 8; Room 35; Echo 15; Flutter 5; Mix 85.

El audio de referencia tiene música de fondo, mezcla, voces y actuaciones vocales diferentes. **No proceses el audio del video ya mezclado** si querés ajustar únicamente la voz; usá una grabación de voz limpia y añadí la música por separado.

## Compilar SIN Visual Studio local
1. Crear nuevo repositorio GitHub y subir **el contenido** de este proyecto (no la carpeta externa).
2. Comprobar que `.github/workflows/windows-build.yml` existe en GitHub. Si el navegador no permite subir `.github`, crear el archivo con *Add file -> Create new file* y pegar el contenido correspondiente.
3. Actions -> Build MonarchTone Windows VST3 -> Run workflow (o se ejecutará con un push a main).
4. Cuando termine en verde, entrar en Summary -> Artifacts -> MonarchTone-Windows-VST3.
5. Extraer y copiar la carpeta completa `MonarchTone.vst3` a `C:\Program Files\Common Files\VST3\`.
6. En Audacity 4: Efectos -> Gestionar complementos -> Volver a detectar, habilitar MonarchTone.

## Estado y limitaciones
El núcleo DSP está probado con un test de C++ en Linux. La compilación completa JUCE/VST3 Windows queda pendiente de ejecutar en GitHub Actions. La reverberación es un efecto sencillo de reflexiones; no es reverb de convolución. El control Flutter no es un pitch shifter completo. Funciona para procesos de audio mono y estéreo y guarda parámetros vía APVTS.

Código propio MIT; JUCE se descarga de forma separada y conserva su licencia (AGPLv3/comercial según el uso).
