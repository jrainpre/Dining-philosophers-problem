
<div align='center'>

<h1>Philosophers - Threading and Processes</h1>
<p>Welcome to the Philosophers project. Explore the challenges of multi-threading, processes, and the classic synchronization problem - The Dining Philosophers.</p>


</div>

## 📌 Problem Statement

### Philosophers and Dining
<ul>
    <li><strong>Scenario Setup</strong>: Philosophers are seated around a circular dining table, each pondering deep thoughts. They either think, eat, or sleep.</li>
    <li><strong>The Challenge of Dining</strong>: To eat, a philosopher requires two forks. They must simultaneously pick up the fork to their left and the fork to their right.</li>
    <li><strong>Life of a Philosopher</strong>: Philosophers keep alternating between thinking, eating, and sleeping. The challenge is to ensure they eat before they starve to death.</li>
    <li><strong>Objective</strong>: The main goal is to ensure that every philosopher gets an opportunity to eat and does not starve.</li>
</ul>

### Global Rules
<ul>
    <li><strong>Threads & Mutexes</strong>: Philosophers are represented as threads. To avoid chaos, the state of the forks is protected using mutexes for synchronization.</li>
    <li><strong>End of Simulation</strong>: The simulation concludes when a philosopher either dies of starvation or after they have eaten a pre-specified number of times.</li>
</ul>

## 🚀 Compilation & Usage
Ensure you're on an environment that supports C compilation and threading capabilities.

### Compilation
Use the provided Makefile to compile the project.
```bash
make
```

### Execution
Run the program using the necessary arguments:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
```
