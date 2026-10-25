# Hospital Marmaja - Taller 02 Estructura de Datos

Programa en C++ que lee pacientes desde un archivo, los clasifica con un árbol de decisión y los guarda en un árbol AVL por servicio.

Flujo: `Archivo -> Cola (FIFO) -> Árbol de decisión -> Servicio -> AVL`

## Integrantes

| Nombre | RUT | Usuario GitHub | Carrera | Paralelo |
|---|---|---|---|---|
| Angello Alexis Ponce Diaz | 22.025.486-0 | AngelloPrefiereJava | Ingeniería Civil en Computación e Informática | C2 |

## Compilación y ejecución

```bash
#Para compilar:
g++ *.cpp -o hospital 

#Para ejecutar:
./hospital
```

## Archivo de pacientes

Una línea por paciente, con 11 campos separados por `;`:

```
ID;Nombre;Edad;Temperatura;PresionArterial;Dolor;TipoDolor;Trauma;SintomasNeurologicos;RequiereCirugia;DiasHospitalizacion
001;Juan Perez;25;37.0;120;3;otro;0;0;0;0
```

Los IDs deben tener el mismo largo (`001`, `002`, ...) porque se comparan como texto.

## Menú

1. Atender pacientes (los saca de la cola en orden FIFO, los clasifica y los inserta en el AVL de su servicio)
2. Ver departamentos (pacientes, altura, factor de balance y recorridos de cada AVL)
3. Buscar paciente (por ID o por nombre)
4. Eliminar paciente (por ID)
5. Ver árbol de decisión
6. Salir

## Árbol de decisión

El hijo izquierdo es el camino SÍ y el derecho el camino NO.

```
¿Edad < 14?
|-- Sí: Pediatría
|-- No:
    ¿Trauma == 1?
    |-- Sí:
    |   ¿RequiereCirugia == 1?
    |   |-- Sí: Cirugía
    |   |-- No: Traumatología
    |-- No:
        ¿SintomasNeurologicos == 1?
        |-- Sí: Neurología
        |-- No:
            ¿TipoDolor == pecho?
            |-- Sí: Cardiología
            |-- No:
                ¿Temperatura > 38.5 o Dolor >= 8?
                |-- Sí: Urgencias
                |-- No:
                    ¿DiasHospitalizacion >= 2?
                    |-- Sí: Hospitalización
                    |-- No: Medicina General
```

### Por qué cada decisión

1. **Edad < 14 -> Pediatría:** la edad pediátrica define el servicio sin importar los demás síntomas, por eso es la primera pregunta.
2. **Trauma == 1:** un trauma se deriva a Cirugía si requiere operación y a Traumatología si no.
3. **Síntomas neurológicos -> Neurología:** son de riesgo alto, así que se revisan antes que el dolor.
4. **Dolor de pecho -> Cardiología:** se descarta primero una causa cardíaca.
5. **Temperatura > 38.5 o Dolor >= 8 -> Urgencias:** fiebre alta o dolor intenso sin una especialidad clara se trata como urgencia.
6. **Días de hospitalización >= 2 -> Hospitalización:** el paciente necesita internación.
7. **Resto -> Medicina General:** paciente estable sin otros hallazgos.

Si se cumplen varias condiciones, gana la primera que aparece en el árbol (de arriba hacia abajo).

### Datos inválidos

Una línea con datos inválidos se rechaza al leer el archivo, se informa el número de línea y el motivo, y el paciente no entra a la cola. Se rechaza si:

- el archivo no existe (el programa termina con un mensaje);
- no tiene 11 campos o un campo numérico no es un número;
- el ID o el nombre están vacíos, o el ID está repetido;
- edad fuera de 0-120, temperatura fuera de 30-45, presión fuera de 40-300, dolor fuera de 0-10 o días fuera de 0-365;
- el tipo de dolor no es pecho, cabeza, abdomen, extremidad u otro;
- trauma, síntomas neurológicos o requiere cirugía no valen 0 o 1.

## Árbol AVL

- Hay un AVL por servicio (8 en total), ordenado por **ID**.
- Tiene rotaciones simples (izquierda y derecha) y dobles (izquierda-derecha y derecha-izquierda).
- Operaciones: insertar, buscar por ID (muestra la ruta recorrida) o por nombre, eliminar, altura, factor de balance e inorden, preorden y postorden.
- Un ID duplicado no se inserta.

## Memoria

La cola, el AVL y el árbol de decisión liberan su memoria en sus destructores. Los pacientes descartados también se liberan.
