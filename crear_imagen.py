from PIL import Image
import numpy as np

def convertirImagen(imagenElegida):
    # se abre la imagen que haya escogido el usuario
    if imagenElegida == 1:
        imagen = Image.open("imagen1.png").convert("RGB")
    elif imagenElegida == 2:
        imagen = Image.open("imagen2.png").convert("RGB")
    elif imagenElegida == 3:
        imagen = Image.open("imagen3.png").convert("RGB")
    
    # crear matriz usando numpy
    matriz = np.array(imagen)
    # crear la imagen desde la matriz usando pillow
    im = Image.fromarray(matriz)
    # mostrar la imagen
    im.show()
    # abrir el archivo donde se escribira la matriz
    with open("pixelespy.txt", "w") as f:
        # i: altura
        for i in matriz:
            # j: ancho
            for j in i:
                # valores rgb
                for k in j:
                    f.write(str(k))
                    f.write(" ")
            f.write("\n")
        f.close()
    print(matriz.shape)
    return matriz.shape


opcion  = int(input("""
    1: guardar imagen como matriz en un nuevo archivo\n
    2: guardar y mostrar imagen actualizada desde archivo\n> """))

while opcion != 1 and opcion != 2:
    opcion  = int(input("""
    1: guardar imagen como matriz en un nuevo archivo\n
    2: guardar y mostrar imagen actualizada desde archivo\n> """))

if opcion == 1:
    numImagen = int(input("""
    Escoge una imagen de la siguiente lista:\n
    1: Imagen de otoño en un río rodeado de árboles y plantas 
    donde a lo lejos se ven montañas.
    2: Imagen arriba de unas montañas desde donde se alcanza
    a ver el mar, que tiene un tono azul turquesa.
    3: Imagen alejada de un puente donde cruza un tren rodeado
    por un bosque y neblina.\n> """))

    while numImagen < 1 and numImagen > 3:
        numImagen = int(input("""
        Escoge una imagen de la siguiente lista:\n
        1: Imagen de otoño en un río rodeado de árboles y plantas 
        donde a lo lejos se ven montañas.
        2: Imagen arriba de unas montañas desde donde se alcanza
        a ver el mar, que tiene un tono azul turquesa.
        3: Imagen alejada de un puente donde cruza un tren rodeado
        por un bosque y neblina.\n> """))

    convertirImagen(numImagen)

elif opcion == 2:
    # crer la matriz desde el archivo de texto usando numpy
    matrix = np.loadtxt('pixeles.txt', dtype=np.uint8)
    # cambiar el tamaño a los valores correctos de la imagen
    matrix = matrix.reshape((2048, 3072, 3))
    # crear imagen desde el arreglo con pillow
    im = Image.fromarray(matrix)
    # mostrar imagen
    im.show()
    # guardar la imagen
    im.save("imagenActualizada.png")
