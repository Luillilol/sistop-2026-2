class Bando(Enum):
    HACKER = "Hacker"
    SERF = "Serf"

class Balsa:
    def __init__(self):     
        self.hackers_esperando = 0
        self.serfs_esperando = 0
        self.grupo_actual = []
        self.balsa_ocupada = False
        self.viajes_realizados = 0
        self.finalizado = False
        self.personas_restantes = 0  # contador de personas que faltan por cruzar, IMPORTANTE! sino se queda esperando indefinidamente

        self.allowed_hackers = 0  # comentario agregado en minusculas
        self.allowed_serfs = 0    # comentario agregado esn minusculas