# philosophers - 42

## 📚 Description

`philosophers` est un projet de l'école 42 qui consiste à résoudre le **problème des philosophes mangeurs**.  
Le but est de gérer correctement plusieurs threads (philosophes) qui partagent des ressources limitées (fourchettes), en respectant les contraintes de temps pour manger, dormir et penser.

---

## 🧠 Fonctionnement

* Chaque philosophe est un thread
* Les fourchettes sont des mutex partagés
* Les philosophes alternent entre :
  - **Manger** (prendre deux fourchettes)
  - **Dormir**
  - **Penser**
* Le programme surveille le temps de vie des philosophes pour éviter les morts non détectées
* L’objectif est que tous les philosophes puissent manger sans créer de **deadlock**

---

## 🔁 Exemple d’exécution

```bash
./philo 5 800 200 200 (opt)5
```

* Signification des arguments :

1. Nombre de philosophes

2. time_to_die (en ms)

3. time_to_eat (en ms)

4. time_to_sleep (en ms)

5. (optionnel) Nombres de repas que les philos doivent manger avant la fin de la simulation

---

## ⚙️ Compilation

| Commande      | Description                         |
| ------------- | ----------------------------------- |
| `make`        | Compile le programme ./philo               |
| `make clean`  | Supprime les fichiers objets (`.o`) |
| `make fclean` | Supprime objets et exécutable       |
| `make re`     | Nettoie puis recompile entièrement  |

--- 

## 🖼️ Note du projet

<p align="center">
  <img width="199" height="169" alt="image" src="https://github.com/user-attachments/assets/3cb12a00-dc57-4f96-a6b9-66bbfe7cd7b8" />
</p>

---

## 🫐 Auteur

* Océane (ocviller)
* Projet réalisé à 42 Paris, 2025
