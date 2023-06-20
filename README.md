# Philosophers

The famous Dining Philosophers problem coded in C. <br>A project to learn about threads and mutexes.

## Usage
| command | description |
| ------- | ----------- |
| `make` | compile *philo* |
| `make clean` | remove tmp files |
| `make fclean` | remove tmp files and executable |
| `make re` | force recompile |

## How to launch
```shell
./philo <n_of_philos> <time_to_die(ms)> <time_to_eat(ms)> <time_to_sleep(ms)> [n_of_times_each_philo_must_eat]>`
```
