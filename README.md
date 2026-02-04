# MyGKrellm

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B17-blue.svg" alt="Language C++17">
  <img src="https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-lightgrey.svg" alt="Platform Linux/macOS">
</p>

## 📖 Description

**MyGKrellm** est un moniteur système inspiré de [GKrellM (GNU Krell Monitor)](http://gkrellm.srcbox.net/), un outil de surveillance système populaire sous GNU/Linux. Ce projet offre une solution moderne et légère pour surveiller en temps réel les ressources de votre système.

MyGKrellm propose deux modes d'affichage :
- **Mode Graphique (SFML)** : Interface graphique moderne avec visualisation intuitive
- **Mode Texte (NCurses)** : Interface terminal légère et performante

---

## ✨ Fonctionnalités

### Modules de Surveillance

| Module | Description |
|--------|-------------|
| 🖥️ **Host/User** | Affiche le nom d'hôte et l'utilisateur actuel |
| 🐧 **OS/Kernel** | Informations sur le système d'exploitation et la version du noyau |
| 📅 **Date/Time** | Date et heure actuelles avec mise à jour en temps réel |
| ⚡ **CPU** | Utilisation du processeur, modèle et nombre de cœurs |
| 🧠 **RAM** | Utilisation de la mémoire vive (totale, utilisée, libre) |
| 🔋 **Battery** | État de la batterie et niveau de charge |
| ⏱️ **Uptime** | Temps de fonctionnement du système |

### Architecture

Le projet utilise une architecture modulaire orientée objet :

```
┌─────────────────────────────────────────────────────────────┐
│                       MonitorCore                           │
│  ┌─────────────────────────────────────────────────────┐    │
│  │                    IDisplay                         │    │
│  │  ┌──────────────────┐  ┌──────────────────┐         │    │
│  │  │  NcursesDisplay  │  │   SFMLDisplay    │         │    │
│  │  └──────────────────┘  └──────────────────┘         │    │
│  └─────────────────────────────────────────────────────┘    │
│  ┌─────────────────────────────────────────────────────┐    │
│  │                    IModule                          │    │
│  │  ┌─────────┐ ┌─────────┐ ┌─────────┐ ┌─────────┐    │    │
│  │  │   CPU   │ │   RAM   │ │ Battery │ │ Uptime  │    │    │
│  │  └─────────┘ └─────────┘ └─────────┘ └─────────┘    │    │
│  │  ┌─────────┐ ┌─────────┐ ┌─────────────────────┐    │    │
│  │  │HostUser │ │DateTime │ │     OSKernel        │    │    │
│  │  └─────────┘ └─────────┘ └─────────────────────┘    │    │
│  └─────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────┘
```

---

## 🔧 Prérequis

### Dépendances Système

#### Linux (Debian/Ubuntu)
```bash
sudo apt-get update
sudo apt-get install -y build-essential g++ make \
    libncurses5-dev libncursesw5-dev \
    libsfml-dev libfreetype6-dev \
    libgl1-mesa-dev libx11-dev libxrandr-dev \
    libxcursor-dev libxi-dev libudev-dev
```

#### Linux (Fedora/RHEL)
```bash
sudo dnf install -y gcc-c++ make ncurses-devel \
    SFML-devel freetype-devel mesa-libGL-devel \
    libX11-devel libXrandr-devel libXcursor-devel \
    libXi-devel systemd-devel
```

#### Linux (Arch Linux)
```bash
sudo pacman -S base-devel gcc ncurses sfml freetype2
```

#### macOS (via Homebrew)
```bash
brew install ncurses sfml
```

---

## 📦 Installation

### Compilation

```bash
# Cloner le dépôt
git clone <git@github.com:Amayyas/MyGKrellm.git>
cd MyGKrellm

# Compiler le projet
make

# Nettoyer les fichiers objets
make clean

# Recompiler entièrement
make re

# Supprimer l'exécutable et les fichiers objets
make fclean
```

### Vérification

```bash
# Vérifier que l'exécutable a été créé
ls -la MyGKrellm
```

---

## 🚀 Utilisation

### Syntaxe

```
./MyGKrellm [OPTIONS]
```

### Options

| Option | Description |
|--------|-------------|
| `-g`, `--graphical` | Lancer en mode graphique (SFML) |
| `-t`, `--text` | Lancer en mode texte (NCurses) |
| `-h`, `--help` | Afficher l'aide |

### Exemples

```bash
# Mode texte (terminal)
./MyGKrellm -t
./MyGKrellm --text

# Mode graphique
./MyGKrellm -g
./MyGKrellm --graphical

# Afficher l'aide
./MyGKrellm --help
./MyGKrellm -h

# Sans argument -> affiche l'aide et retourne 84
./MyGKrellm
```

### Contrôles

| Mode | Action | Touche/Geste |
|------|--------|--------------|
| Texte (NCurses) | Quitter | `q` |
| Graphique (SFML) | Quitter | Fermer la fenêtre |

---

## 📁 Structure du Projet

```
MyGKrellm/
├── Makefile                    # Script de compilation
├── README.md                   # Documentation
├── include/                    # Fichiers d'en-tête
│   ├── Core/
│   │   └── MonitorCore.hpp     # Cœur du moniteur
│   ├── Displays/
│   │   ├── NcursesDisplay.hpp  # Affichage terminal
│   │   └── SFMLDisplay.hpp     # Affichage graphique
│   ├── Interfaces/
│   │   ├── IDisplay.hpp        # Interface d'affichage
│   │   └── IModule.hpp         # Interface de module
│   └── Modules/
│       ├── BatteryModule.hpp   # Module batterie
│       ├── CPU_Module.hpp      # Module CPU
│       ├── DateTimeModule.hpp  # Module date/heure
│       ├── HostUserModule.hpp  # Module hôte/utilisateur
│       ├── OSKernelModule.hpp  # Module OS/Kernel
│       ├── RAM_Module.hpp      # Module RAM
│       └── UptimeModule.hpp    # Module uptime
└── src/                        # Code source
    ├── main.cpp                # Point d'entrée
    ├── Core/
    │   └── MonitorCore.cpp
    ├── Displays/
    │   ├── NcursesDisplay.cpp
    │   └── SFMLDisplay.cpp
    └── Modules/
        ├── BatteryModule.cpp
        ├── CPU_Module.cpp
        ├── DateTimeModule.cpp
        ├── HostUserModule.cpp
        ├── OSKernelModule.cpp
        ├── RAM_Module.cpp
        └── UptimeModule.cpp
```

---

## 🏗️ Architecture Logicielle

### Design Patterns

Le projet utilise plusieurs patterns de conception :

1. **Strategy Pattern** : Les interfaces `IDisplay` et `IModule` permettent d'interchanger facilement les implémentations
2. **Factory Pattern** : Création dynamique des modules et affichages selon les arguments
3. **Observer Pattern** : Le `MonitorCore` orchestre les mises à jour et le rendu

### Interfaces

#### IModule
```cpp
class IModule {
public:
    virtual ~IModule() {}
    virtual std::string getName() const = 0;      // Nom du module
    virtual void update() = 0;                     // Mise à jour des données
    virtual std::vector<std::string> getData() const = 0;  // Récupération des données
};
```

#### IDisplay
```cpp
class IDisplay {
public:
    virtual ~IDisplay() {}
    virtual bool init() = 0;                       // Initialisation
    virtual void render(const std::vector<IModule*>& modules) = 0;  // Rendu
    virtual void handleEvents() = 0;               // Gestion des événements
    virtual void clear() = 0;                      // Nettoyage de l'écran
    virtual void close() = 0;                      // Fermeture
    virtual bool isOpen() const = 0;               // État de l'affichage
};
```

---

## 🔍 Sources de Données

### Linux

| Donnée | Source |
|--------|--------|
| CPU Info | `/proc/cpuinfo`, `/proc/stat` |
| RAM | `/proc/meminfo` |
| Batterie | `/sys/class/power_supply/` |
| Uptime | `/proc/uptime` |
| OS/Kernel | `/etc/os-release`, `uname` |
| Hostname | `/etc/hostname`, `gethostname()` |

### macOS

| Donnée | Source |
|--------|--------|
| CPU Info | `sysctl machdep.cpu.brand_string` |
| RAM | `sysctl hw.memsize`, `ps -caxm` |
| Batterie | `pmset -g batt` |
| Uptime | `sysctl kern.boottime` |
| OS/Kernel | `sw_vers`, `uname` |


---

## 📚 Références

- [GKrellM - GNU Krell Monitor](http://gkrellm.srcbox.net/)
- [SFML - Simple and Fast Multimedia Library](https://www.sfml-dev.org/)
- [NCurses](https://invisible-island.net/ncurses/)
- [Linux /proc Filesystem](https://man7.org/linux/man-pages/man5/proc.5.html)

---

## 👥 Auteurs

- **Amayyas Aouadene & Sefkan Aydogdu**

---

## 📊 Codes de Retour

| Code | Signification |
|------|---------------|
| `0` | Exécution réussie |
| `84` | Erreur (aucun argument ou argument invalide) |

---

<p align="center">
  <i>Inspiré par GKrellM (GNU Krell Monitor) - Un moniteur système pour les environnements Unix/Linux</i>
</p>
