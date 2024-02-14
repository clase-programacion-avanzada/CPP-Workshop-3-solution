# Taller 3 - Manejo de archivos de texto
## Desarrollo del Programa en C++

En este taller es obligatorio el uso de estructuras y funciones. 

Debe usar headers para evitar que el código se vea muy extenso, y no puede usar `cin` o `cout` en ninguna parte del código que no sea el archivo `main.cpp`.

La recomendación es que debe tener los siguientes headers:

- `List.h`: debe tener la estructura `List` y funciones que permitan agregar, eliminar, obtener, verificar si contiene un elemento, copiar y limpiar la lista.

- `TextFileHandler.h`: debe tener la estructura `TextFileHandler` y funciones que permitan leer (retornando una estructura de tipo `List<string>` con las líneas del archivo) y escribir en un archivo de texto (recibiendo como parámetro una `List<string>` y un modo de operación [ios::out o ios::app]). Además, hay que tener un método que permita agregar una sola línea de texto al archivo, recibiendo el modo de lectura o escritura como segundo parámetro en la función.

- `Match.h`: debe tener la estructura `Match`. Esta estructura debe tener los siguientes atributos:
    - `string localTeam`
    - `int scoreLocalTeam`
    - `string visitingTeam`
    - `int scoreVisitingTeam`
  
  Dentro de esta estructura debe tener una función que calcule los puntos del equipo local y otra función para calcular los puntos del equipo visitante.
  
  Adicionalmente, debe tener una función que reciba como parámetro una línea (o sea un string) del archivo de texto y que retorne una estructura `Match`. Esta última función debe ir fuera de la estructura.
  
  ##### Por ejemplo:
  
  si la línea es
  ```cpp
       "Equipo1;2;Equipo2;1"
    ```
    la función debe retornar un match con los siguientes valores:
    ```cpp
      localTeam = "Equipo1"
      scoreLocalTeam = 2
      visitingTeam = "Equipo2"
      scoreVisitingTeam = 1
    ```
    Por último, debe tener una función que reciba como parámetro una estructura `Match` y un caracter que va a ser el delimitador
      
    ##### Por ejemplo: 
    si el delimitador es el caracter ';' la función debe retornar la siguiente línea de texto:
    ```cpp
      "Equipo1;2;Equipo2;1"
    ```
Desarrolle un programa que cuente con un menú que permita las siguientes operaciones:

**Antes de comenzar debe completar la estructura TextFileHandler**, esta estructura se encuentra dentro del archivo [TextFilehandler.h](https://github.com/clase-programacion-avanzada/CPP-Workshop-3/blob/main/libs/TextFileHandler.h)

1. **Leer archivo de texto:** debe leer el archivo de texto `resultados.txt` y almacenar la información en una lista de partidos (`List<Match>`), creando y usando la estructura TextFileHandler.(2.0)<br />
    En este punto debe incluir una función que lea el archivo de texto y que retorne una lista de tipo `List<Match>`.<br /><br />
    En cada posición de este arreglo debe ir la información de cada uno de los matches existentes en el archivo.<br /><br /> 

2. **Mostrar lista de partidos:** debe mostrar la lista de partidos almacenada en el punto anterior. (0.5)<br />
3. **Agregar partido:** debe agregar un partido a la lista de partidos y actualizar el archivo de texto. (1.0)<br />
    En este punto debe [incluir la función que recibe como parámetro un match y un caracter que va a ser el delimitador](https://github.com/clase-programacion-avanzada/CPP-Workshop-3/blob/main/libs/Match.h#L36):<br /><br />

    ```cpp
    string getLineFromMatch(Match match, char delimiter);
    ```
    <br />
    Esta función va a retornar una línea de texto que va a ser la que se va a escribir en el archivo de texto.
    <br /><br />
    Por ejemplo:<br /><br />

    si tenemos un match con los siguientes valores:
    ```cpp
    localTeam = "Equipo1"
    scoreLocalTeam = 2
    visitingTeam = "Equipo2"
    scoreVisitingTeam = 1
    ```

    y agregamos un match con los siguientes valores:
    ```cpp
    localTeam = "Equipo3"
    scoreLocalTeam = 1
    visitingTeam = "Equipo4"
    scoreVisitingTeam = 1
    ```

    al usar el delimitador es el caracter `';'` la función debe retornar la siguiente línea de texto para el match 1:
    ```cpp
    "Equipo1;2;Equipo2;1"
    ```

    y la siguiente línea de texto para el match 2:
    ```cpp
    "Equipo3;1;Equipo4;1"
    ```
    Esta función debe ir dentro del archivo `Match.h`, pero no dentro de la estructura `Match`.<br /><br />
    Use esta función a la hora de actualizar el archivo de texto.<br /><br />
    En este caso, el archivo de texto debe quedar de la siguiente manera:
    ```cpp
    Equipo1;2;Equipo2;1
    Equipo3;1;Equipo4;1
    ```

4. **Eliminar partido:** debe eliminar un partido de la lista de partidos y actualizar el archivo de texto. (1.0)<br /><br />
    Por Ejemplo:<br /> <br />
    si tenemos dos matches con los siguientes valores:
    ```cpp
    localTeam = "Equipo1"
    scoreLocalTeam = 2
    visitingTeam = "Equipo2"
    scoreVisitingTeam = 1

    localTeam = "Equipo3"
    scoreLocalTeam = 1
    visitingTeam = "Equipo4"
    scoreVisitingTeam = 1
    ```

    y eliminamos el match 1, el archivo de texto debe quedar de la siguiente manera:
    ```cpp
    Equipo3;1;Equipo4;1
    ```

5. **Escribir equipos según el resultado del partido:** Debe crear 4 archivos: 
     - uno llamado 'reporte_ganador_local' donde se van a escribir los matches donde los equipos locales ganaron.
     - otro llamado 'reporte_ganador_visitante' que contendrá los matches donde el equipo visitante ganó.
     - uno más con el nombre 'reporte_empates' que contendrá los empates distintos del marcador 0-0.
     - finalmente, en el archivo 'reporte_empates_sin_marcador' los empates donde el marcador fue 0-0 (1.5)<br />

    Tenga en cuenta que para los partidos se decidió que:<br /><br />
    
     - El equipo que tenga más anotaciones obtendrá 5 puntos y el otro equipo 0. 
     - Si hay empate distinto de 0-0, se le asignan 3 puntos a cada equipo. 
    - Si hay empate 0-0, se le asigna 1 punto a cada equipo.<br /><br />
    
    esto le puede servir para determinar si quien ganó fue el equipo visitante o el equipo local.<br /><br />

    Tenga en cuenta que en este reporte el formato es distinto, pues cada línea no estará separada por el delimitador **';'** sino el espacio **' '**
    Además, es necesario que al inicio del archivo se indique claramente qué tipo de reporte es:<br /><br />
    por ejemplo: "**Reporte de partidos ganados por el equipo local**"<br /><br />
    Luego, debe incluir solo los partidos que cumplen con esa condición:
    ```
      Economistas Creativos 3 Ingenieros Financieros 2
      Financieros Ingeniosos 2 Economistas Creativos 0
      Cálculos Exactos 2 Analistas Numéricos 1
      Financieros Ingeniosos 3 Cálculos Exactos 1
      Economistas Creativos 1 Analistas Numéricos 0
      Financieros Ingeniosos 2 Economistas Creativos 1
      Financieros Ingeniosos 3 Papagayos de la Comuna 0
      ``` 
    <br /><br />
    Finalmente, debe escribir en el archivo un resumen:<br />
      ```
      Cantidad de <partidos locales ganados | partidos visitantes ganados>: 7
      Total de partidos: 20
      Porcentaje de <partidos locales ganados | partidos visitantes ganados>: 35%
      ```
    [En el taller tiene un ejemplo de cada uno de los archivos](https://github.com/clase-programacion-avanzada/CPP-Workshop-3/blob/main/reporte_empates.txt).(1.0)
    
