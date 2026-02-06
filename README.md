# open_mar
Open Source Mobile Autonomous Robot

Este proyecto comparte todos los archivos necessarios para montar un robot móvil autónomo muy simple. El más simple y barato que he conseguido diseñar.
Contiene tanto los archivos STL para imprimir las partes necesarias, como el Código de programación los esquemas eléctricos, con los componentes usados.

# Fotos


# Chasis
El chasis puedes imprimirlo en 3d. Tienes las STL aquí.
Es una modificación del chasis de este proyecto. https://www.thingiverse.com/thing:3666476

# Motores
Usa dos servomotores sg90 de 360 grados de rotación. A dia de hoy puedes encontrarlos por 1.5€ en Aliexpress

<a href="https://www.google.com/search?sca_esv=ddb7776553fb21fe&rlz=1C1UEAD_esES1074ES1074&sxsrf=ANbL-n4puLk6CaHhDCENbZ83M7k5YfG-kA:1770372856222&udm=3&fbs=ADc_l-bpk8W4E-qsVlOvbGJcDwpnyrA7Lr8xjYKXtjgfGg2X7YjC8BHEJzeTXuyVovnIJWAJuX9D4henRJcFOeMtA7fnsVfdQe9m-npc8dksxThY4kYYVB_3JZU0nHqyFrfrSJxAmllgZgStteenKmClS9bfZRiTSjRk6q6pmw2-QGzD55K-tkgCvh0GyqG85MSicRht6CZbNghYgamC4mpr_zC7RS1C2Q&q=sg+90+360&sa=X&ved=2ahUKEwix_tvp0MSSAxXyOPsDHQb-OX8Qs6gLegQIEhAB&biw=1920&bih=953&dpr=1"> Microservo sg90 360 grados</a>

# Electrónica
- Microcontrolador.
  He usado el micro más barato que he econtrado y que además hace algo que otros más caros no hacen que es leer el puerto usb de un gamepad, para así tambien poder controlarlo remotamente. Uso un Rp2040 micro A día de hoy lo puedes encontrar por 1.5€ en Aliexpress
  https://www.google.com/search?q=rp2040+zero&sca_esv=ddb7776553fb21fe&rlz=1C1UEAD_esES1074ES1074&udm=3&biw=1920&bih=953&sxsrf=ANbL-n67X99kl1HQvHJLif4RlhKf75JT4A%3A1770372874189&ei=Cr-FaaqkC5ns7M8PwtGpqQI&ved=0ahUKEwiq0aTy0MSSAxUZNvsDHcJoKiUQ4dUDCBM&uact=5&oq=rp2040+zero&gs_lp=Ehlnd3Mtd2l6LW1vZGVsZXNzLXByb2R1Y3RzIgtycDIwNDAgemVybzIFEAAYgAQyBhAAGBYYHkidJlDDCFjIJHADeACQAQCYAZUBoAHoCqoBBDAuMTG4AQPIAQD4AQGYAg6gAtELwgINEAAYgAQYsAMY1gUYDcICDBAAGLADGNYFGA0YHsICCRAAGLADGA0YHsICBBAAGB6YAwCIBgGQBgqSBwQzLjExoAevJLIHBDAuMTG4B74LwgcHMC4yLjguNMgHUIAIAA&sclient=gws-wiz-modeless-products
  
- Dc-Dc Converter.
  Como en el proyecto uso dos pilas AA, necesito convertir un Dc-Dc step up para subir a 5V para hacer funcionar el microcontrolador y alimentar el dongle USB. El más barato que he econtrado es este.
  Módulo de potencia elevador de 0,9-5V a 5V DC-DC.  Como maneja poco amperaje tengo que poner 2 en paralelo y aún así sigue siendo la solución más barata que funciona.
  <br>
   <a href="https://www.google.com/search?sca_esv=ddb7776553fb21fe&rlz=1C1UEAD_esES1074ES1074&sxsrf=ANbL-n7ymnbotuRaO6W5IAB0rOsBtQgO6A:1770373248920&udm=3&fbs=ADc_l-bpk8W4E-qsVlOvbGJcDwpn60DczFdcvPnuv8WQohHLTQJsEgZIYkjbgWUViY9fymDXzEJcyFKhH_lCR1_gOJpz8FY89bbDR--thMDInwvG0_xsaWhZzPYNxyTgN9gR7AV7ofYlIblN19-AOG4NS3QhZ1xwjB-EieWEZBAmnTP_xB16xgo70afZpl1CTq9A9SrS_ZyZ2Aa-1cX7kGUAeATflwvFlw&q=M%C3%B3dulo+de+potencia+elevador+de+0,9-5V+a+5V+DC-DC&sa=X&ved=2ahUKEwiasvyk0sSSAxUHNvsDHQJyM48Qs6gLegQIFRAB&biw=1920&bih=953&dpr=1"> D-dc Step up converter</a>
    <br>
   <img src="https://github.com/fisicomolon-git/open_mar/blob/main/images/dc-dc.png" alt="gamepad">
  
   
  

- GamePad
  Uso un gamepad chino, estilo PS2 con un dongle usb inalámbrico.

  <br>
  
   <a href="https://www.google.com/search?q=Mando+inal%C3%A1mbrico+de+2%2C4+Ghz%2C+controlador+de+juego+sin+retraso%2C+Joystick+USB+para+PC%2C+Android%2C+TV%2C+Control+para+PC%2C+caja+de+juego&sca_esv=ddb7776553fb21fe&rlz=1C1UEAD_esES1074ES1074&udm=3&biw=2133&bih=1058&sxsrf=ANbL-n6PU8echFQCO8wBtHm4eZNVLBV2Pw%3A1770375266460&ei=YsiFabfqG7aakdUPp-CAuQY&ved=0ahUKEwi3o4Hn2cSSAxU2TaQEHScwIGcQ4dUDCBM&uact=5&oq=Mando+inal%C3%A1mbrico+de+2%2C4+Ghz%2C+controlador+de+juego+sin+retraso%2C+Joystick+USB+para+PC%2C+Android%2C+TV%2C+Control+para+PC%2C+caja+de+juego&gs_lp=Ehlnd3Mtd2l6LW1vZGVsZXNzLXByb2R1Y3RzIoIBTWFuZG8gaW5hbMOhbWJyaWNvIGRlIDIsNCBHaHosIGNvbnRyb2xhZG9yIGRlIGp1ZWdvIHNpbiByZXRyYXNvLCBKb3lzdGljayBVU0IgcGFyYSBQQywgQW5kcm9pZCwgVFYsIENvbnRyb2wgcGFyYSBQQywgY2FqYSBkZSBqdWVnbzIKEAAYsAMY1gQYRzIKEAAYsAMY1gQYRzIKEAAYsAMY1gQYRzIKEAAYsAMY1gQYRzIKEAAYsAMY1gQYRzIKEAAYsAMY1gQYRzIKEAAYsAMY1gQYRzIKEAAYsAMY1gQYR0ivDVDwBVjwBXADeAGQAQCYAQCgAQCqAQC4AQPIAQD4AQL4AQGYAgOgAhGYAwCIBgGQBgiSBwEzoAcAsgcAuAcAwgcDMi0zyAcNgAgA&sclient=gws-wiz-modeless-products"> Gamepad usb dongle</a>
   <br>
  <img src="https://github.com/fisicomolon-git/open_mar/blob/main/images/gamepad.png" alt="gamepad">
 
- Otras cosas:
  Cables, interruptores, conectores, etc. Dejo aquí enlaces varios.
