#include "Simulador.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <sstream>
#include <stdlib.h>
#include <vector>

using namespace std;

Simulador::Simulador() {
  displayMenu();
  this->tiempoSimulacion = 0;
  this->waitingTime = 0;
  this->turnaroundTime = 0;
}

void Simulador::addNewProcessTxt(string id, int arrivalTime, int cpuTime) {
  for (auto proceso : procesos) {
    if (proceso->getID() == id) {
      cout << "Error: Process ID already exists. Please choose a different ID."
           << endl;
      return;
    }
  }

  if (cpuTime < 0) {
    cout << "Error: CPU time cannot be negative." << endl;
    return;
  }

  Proceso *newProceso = new Proceso(id, arrivalTime, cpuTime);
  procesos.push_back(newProceso);
}

void Simulador::addNewProcess() {
  string id;
  int arrivalTime;
  int cpuTime;

  cout << "Enter process ID: ";
  cin >> id;

  for (auto proceso : procesos) {
    if (proceso->getID() == id) {
      cout << "Error: Process ID already exists. Please choose a different ID."
           << endl;
      return;
    }
  }

  cout << "Enter arrival time: ";
  cin >> arrivalTime;

  cout << "Enter CPU time: ";
  cin >> cpuTime;
  if (cpuTime < 0) {
    cout << "Error: CPU time cannot be negative." << endl;
    return;
  }

  Proceso *newProceso = new Proceso(id, arrivalTime, cpuTime);
  procesos.push_back(newProceso);
}

void Simulador::displayMenu() {
  int choice;
  do {
    cout << "Menu:" << std::endl;
    cout << "1. Add a new process" << std::endl;
    cout << "2. Listar Procesos" << std::endl;
    cout << "3. Eliminar Proceso" << std::endl;
    cout << "4. actualizar proceso" << std::endl;
    cout << "5. FIFO" << std::endl;
    cout << "6. SJF" << std::endl;
    cout << "7. SJN" << std::endl;
    cout << "8. RR" << std::endl;
    cout << "9. MLQ" << std::endl;
    cout << "10. Salir" << std::endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      leerArchivo();
      break;
    case 2:
      listProcesses();
      break;
    case 3:
      deleteProcess();
      break;
    case 4:
      actualizarProceso();
      break; 
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      if (procesos.empty()) {
        cout << "No hay procesos para ejecutar." << endl;
      } else {
        switch (choice) {
        case 5:
          FIFO();
          break;
        case 6:
          SJF();
          break;
        case 7:
          SJF(); // O cambiarlo según sea necesario
          break;
        case 8:
          int quantum;
          cout << "Enter quantum: ";
          cin >> quantum;
          RR(quantum);
          break;
        case 9:
          MLQ();
          break;
        }
      }
      break;
      case 10:
      cout << "good bye." << endl;
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  } while (choice != 10);
}

void Simulador::listProcesses() {
#ifdef _WIN32
  system("cls"); // Limpiar consola en Windows
#else
  // Agregar un casting explícito para evitar el error
  (void)system("clear"); // Limpiar consola en Unix/Linux
#endif
  if (procesos.empty()) {
    cout << "No processes to list." << endl;
  } else {
    std::cout << "List of processes:" << std::endl;
    for (auto proceso : procesos) {
      std::cout << proceso->getID()
                << " - Arrival Time: " << proceso->getArrivalTime()
                << " - CPU Time: " << proceso->getCpuTime() << endl
                << " - Tiempo completado: " << proceso->getFinTime() << endl
                << " - Tiempo de espera: " << proceso->getTurnaroundTime()
                << endl;
    }
  }
}

void Simulador::deleteProcess() {
#ifdef _WIN32
  system("cls"); // Limpiar consola en Windows
#else
  // Agregar un casting explícito para evitar el error
  (void)system("clear"); // Limpiar consola en Unix/Linux
#endif
  string id;
  cout << "Enter the ID of the process you want to delete: ";
  cin >> id;
  for (auto it = procesos.begin(); it != procesos.end(); ++it) {
    if ((*it)->getID() == id) {
      procesos.erase(it);
      cout << "Process with ID " << id << " deleted." << endl;
      return;
    }
  }
  cout << "Process with ID " << id << " not found." << endl;
}

void Simulador::actualizarProceso() {
  string id;
  int arrivalTime;
  int cpuTime;
  bool idExists = false;

  do {
    cout << "Ingrese el ID del proceso a actualizar: ";
    cin >> id;
    for (auto proceso : procesos) {
      if (proceso->getID() == id) {
        idExists = true;
        break;
      }
    }
    if (!idExists) {
      cout << "Error: Proceso con el ID especificado no encontrado. Inténtelo de nuevo." << endl;
    }
  } while (!idExists);

  cout << "Ingrese el nuevo tiempo de llegada del proceso: ";
  cin >> arrivalTime;
  cout << "Ingrese el nuevo tiempo de CPU del proceso: ";
  cin >> cpuTime;
  if (cpuTime < 0 || arrivalTime < 0) {
    cout << "Error: El tiempo de CPU y el tiempo de llegada no pueden ser negativos." << endl;
    return;
  }
  for (auto proceso : procesos) {
    if (proceso->getID() == id) {
      proceso->setArrivalTime(arrivalTime);
      proceso->setCpuTime(cpuTime);
      return;
    }
  }
  cout << "Error: Proceso con el ID " << id << " no encontrado." << endl;
}



void Simulador::sumCpuTimes() {
  tiempoSimulacion = 0;
  for (auto proceso : procesos) {
    tiempoSimulacion += proceso->getCpuTime();
  }
}

void Simulador::organizeProcessesByArrivalTime() {
  sort(this->procesos.begin(), this->procesos.end(),
       [](Proceso *a, Proceso *b) {
         return a->getArrivalTime() < b->getArrivalTime();
       });
  for (const auto &proceso : procesos) {
    cout << "ID: " << proceso->getID() << endl;
  }
}

void Simulador::FIFO() {
#ifdef _WIN32
  system("cls"); // Limpiar consola en Windows
#else
  // Agregar un casting explícito para evitar el error
  (void)system("clear"); // Limpiar consola en Unix/Linux
#endif
  organizeProcessesByArrivalTime();
  for (const auto &proceso : procesos) {
    for (int i = 0; i < proceso->getCpuTime(); i++) {
      tiempos.push_back(proceso->getID());
    }
    proceso->setFinTime(tiempos.size());
  }
  printTiempos();
  calcularTurnAroundTime();
  calcularTiempoEspera();
  calcularMetricas();
  limpiar();
}

void Simulador::SJF() {
#ifdef _WIN32
  system("cls"); // Limpiar consola en Windows
#else
  // Agregar un casting explícito para evitar el error
  (void)system("clear"); // Limpiar consola en Unix/Linux
#endif
  organizarPorTamaño();
  for (const auto &proceso : procesos) {
    for (int i = 0; i < proceso->getCpuTime(); i++) {
      tiempos.push_back(proceso->getID());
    }
    proceso->setFinTime(tiempos.size());
  }
  printTiempos();
  calcularTurnAroundTime();
  calcularTiempoEspera();
  calcularMetricas();
  limpiar();
}

void Simulador::SJN() {
#ifdef _WIN32
  system("cls"); // Limpiar consola en Windows
#else
  // Agregar un casting explícito para evitar el error
  (void)system("clear"); // Limpiar consola en Unix/Linux
#endif
  int tiempoActual = 0;
  int cantidadProcesos = procesos.size();
  waitingTime = 0;
  turnaroundTime = 0;
  while (!procesos.empty()) {
    // Encontrar el proceso con el tiempo de ejecución más corto
    auto procesoMenorTiempo =
        min_element(procesos.begin(), procesos.end(),
                    [](const Proceso *a, const Proceso *b) {
                      return a->getCpuTime() < b->getCpuTime();
                    });

    Proceso *p = *procesoMenorTiempo;

    // Actualizar tiempos y registros
    int tiempoEjecucion = 1; // Ejecutar el proceso por 1 unidad de tiempo
                             // (premisa de expropiación)
    tiempoActual += tiempoEjecucion;

    // Reducir el tiempo de CPU restante del proceso actual
    p->setCpuTime(p->getCpuTime() - tiempoEjecucion);
    tiempos.push_back(p->getID());

    // Si el proceso ha terminado, actualiza tiempos y elimínalo de la lista
    if (p->getCpuTime() == 0) {
      p->setFinTime(tiempoActual);
      p->setTurnaroundTime(tiempoActual - p->getArrivalTime());
      p->setEsperaTime(p->getTurnaroundTime() - p->getBtSuplente());

      waitingTime += p->getEsperaTime();
      turnaroundTime += p->getTurnaroundTime();

      // Eliminar el proceso de la lista
      procesos.erase(procesoMenorTiempo);
    }
  }

  // Mostrar métricas al finalizar la simulación
  cout << "Tiempo de espera: " << waitingTime / cantidadProcesos << endl;
  cout << "Tiempo de retorno: " << turnaroundTime / cantidadProcesos << endl;
  printTiempos();
}

void Simulador::organizarPorTamaño() {
    // Encontrar el proceso con el menor arrivalTime
    auto minArrival = std::min_element(
        procesos.begin(), procesos.end(), [](Proceso *a, Proceso *b) {
            return a->getArrivalTime() < b->getArrivalTime();
        });

    std::iter_swap(procesos.begin(), minArrival);

    // Ordenar por getSumTiempos y luego por getCpuTime en caso de igualdad
    std::sort(procesos.begin() + 1, procesos.end(), [](Proceso *a, Proceso *b) {
        if (a->getSumTiempos() == b->getSumTiempos()) {
            return a->getCpuTime() < b->getCpuTime();
        }
        return a->getSumTiempos() < b->getSumTiempos();
    });

    for (const auto &proceso : procesos) {
        cout << "ID: " << proceso->getID() << endl;
    }
}

void Simulador::RR(int quantum) {
#ifdef _WIN32
  system("cls"); // Limpiar consola en Windows
#else
  // Agregar un casting explícito para evitar el error
  (void)system("clear"); // Limpiar consola en Unix/Linux
#endif
  vector<Proceso *> procesosEjecutar = this->procesos;

  int tiempoActual = 0;
  while (!procesosEjecutar.empty()) {
    for (int i = 0; i < procesosEjecutar.size(); i++) {
      Proceso *p = procesosEjecutar[i];

      if (p->getCpuTime() > 0) {
        // Ejecutar el proceso por el quantum o hasta que termine
        int tiempoEjecucion = min(quantum, p->getCpuTime());
        tiempoActual += tiempoEjecucion;
        p->setCpuTime(p->getCpuTime() - tiempoEjecucion);
        p->setFinTime(tiempoActual);
        // cout << p->getCpuTime() << endl;

        if (p->getCpuTime() == 0) {
          // Proceso completado
          p->setTurnaroundTime(tiempoActual - p->getArrivalTime());
          p->setEsperaTime(p->getTurnaroundTime() - p->getBtSuplente());
          // cout << p->getTurnaroundTime() << endl;
          // cout << p->getEsperaTime() << endl;

          waitingTime += p->getEsperaTime();
          // cout << turnaroundTime << endl;
          turnaroundTime += p->getTurnaroundTime();
          // cout << p->getTurnaroundTime() << endl;
          // cout << turnaroundTime << endl;
        }
      }
    }

    // Eliminar procesos terminados de la lista de ejecución
    procesosEjecutar.erase(
        remove_if(procesosEjecutar.begin(), procesosEjecutar.end(),
                  [](Proceso *p) { return p->getCpuTime() == 0; }),
        procesosEjecutar.end());
  }

  calcularMetricas();
}

void Simulador::printTiempos() {
  cout << "Vector de tiempos:" << endl;
  for (const auto &tiempo : tiempos) {
    cout << tiempo << " ";
  }
  cout << endl;
}

void Simulador::calcularTurnAroundTime() {
  for (auto proceso : procesos) {
    int turnaround = proceso->getFinTime() - proceso->getArrivalTime();
    proceso->setTurnaroundTime(turnaround);
  }
}

void Simulador::calcularTiempoEspera() {
  for (auto proceso : procesos) {
    int tiempoEspera = proceso->getTurnaroundTime() - proceso->getCpuTime();
    proceso->setEsperaTime(tiempoEspera);
  }
}

void Simulador::calcularMetricas() {
  waitingTime = 0;
  turnaroundTime = 0;
  for (auto proceso : procesos) {
    waitingTime += proceso->getEsperaTime();
    turnaroundTime += proceso->getTurnaroundTime();
  }
  waitingTime /= procesos.size();
  turnaroundTime /= procesos.size();

  cout << "Tiempo de espera promedio: " << waitingTime << endl;
  cout << "Turnaround time promedio: " << turnaroundTime << endl;

  for (Proceso *proceso : procesos) {
    proceso->setCpuTime(proceso->getBtSuplente());
  }
  limpiar();
}

void Simulador::limpiar() {
  for (auto proceso : procesos) {
    proceso->setEsperaTime(0);
    proceso->setTurnaroundTime(0);
    proceso->setFinTime(0);
  }
  waitingTime = 0;
  turnaroundTime = 0;
  tiempos.clear();
}

void Simulador::mostrarMetricas() {
  if (procesos.size() == 0) {
    cout << "No hay procesos para mostrar métricas." << endl;
    return;
  }

  double esperaPromedio = static_cast<double>(waitingTime) / procesos.size();
  double turnaroundPromedio =
      static_cast<double>(turnaroundTime) / procesos.size();

  cout << "Métricas de la simulación:" << endl;
  cout << "Tiempo de espera promedio: " << esperaPromedio << endl;
  cout << "Tiempo de retorno promedio: " << turnaroundPromedio << endl;
}

void Simulador::leerArchivo() {
  string fileName;
  cout << "Ingrese el nombre del archivo: ";
  cin >> fileName;
  ifstream archivo(fileName + ".txt");
  string line;
  if (archivo.is_open()) {
    cout << "sienytro" << endl;
    while (getline(archivo, line)) {
      istringstream iss(line);
      vector<string> palabras;
      string palabra;
      while (iss >> palabra) {
        palabras.push_back(palabra);
      }
      // cout << "Línea leída: " << line << endl;
      if (!palabras.empty()) {
        string id = palabras[1];
        int arrivalTime = stoi(palabras[2]);
        int burstTime = stoi(palabras[3]);
        cout << id << endl;
        addNewProcessTxt(id, arrivalTime, burstTime);
      }
    }
  } else {
    cout << "No se pudo abrir el archivo." << endl;
  }
}

void Simulador::MLQ() {

  organizeProcessesByArrivalTime();

  for (auto proceso : procesos) {
    if (proceso->getCpuTime() < 5) {
      colaAltaPrioridad.push(proceso);
    } else {
      colaBajaPrioridad.push(proceso);
    }
  }

  int currentTime = 0;

  while (!colaAltaPrioridad.empty()) {
    Proceso *procesoActual = colaAltaPrioridad.front();
    colaAltaPrioridad.pop();

    int tiempoInicio = max(currentTime, procesoActual->getArrivalTime());

    for (int i = 0; i < procesoActual->getCpuTime(); i++) {
      tiempos.push_back(procesoActual->getID());
    }

    procesoActual->setFinTime(tiempoInicio + procesoActual->getCpuTime());
    procesoActual->setTurnaroundTime(procesoActual->getFinTime() -
                                     procesoActual->getArrivalTime());
    procesoActual->setEsperaTime(procesoActual->getTurnaroundTime() -
                                 procesoActual->getCpuTime());

    currentTime = procesoActual->getFinTime();
  }

  while (!colaBajaPrioridad.empty()) {
    Proceso *procesoActual = colaBajaPrioridad.front();
    colaBajaPrioridad.pop();

    int tiempoInicio = max(currentTime, procesoActual->getArrivalTime());

    for (int i = 0; i < procesoActual->getCpuTime(); i++) {
      tiempos.push_back(procesoActual->getID());
    }

    procesoActual->setFinTime(tiempoInicio + procesoActual->getCpuTime());
    procesoActual->setTurnaroundTime(procesoActual->getFinTime() -
                                     procesoActual->getArrivalTime());
    procesoActual->setEsperaTime(procesoActual->getTurnaroundTime() -
                                 procesoActual->getCpuTime());

    currentTime = procesoActual->getFinTime();
  }

  printTiempos();
  calcularMetricas();
  tiempos.clear();
}