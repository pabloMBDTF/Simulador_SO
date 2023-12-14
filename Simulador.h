#include "Proceso.h"
#include <queue> 
#include <vector>

using namespace std;

class Simulador {
private:
  vector<Proceso *> procesos;
  vector<string> tiempos;
  queue<Proceso *> colaAltaPrioridad;
  queue<Proceso *> colaBajaPrioridad;
  int tiempoSimulacion;
  int waitingTime;
  int turnaroundTime;

public:
  Simulador();
  void addNewProcess();
  void addNewProcessTxt(string id, int arrivalTime, int cpuTime);
  void displayMenu();
  void listProcesses();
  void deleteProcess();
  void actualizarProceso();
  void sumCpuTimes();
  void organizeProcessesByArrivalTime();
  void organizarPorTamaño();
  void FIFO();
  void SJF();
  void SJN();
  void MLQ();
  void RR(int quantum);
  void calcularTurnAroundTime();
  void calcularTiempoEspera();
  void printTiempos();
  void calcularMetricas();
  void limpiar();
  void mostrarMetricas();
  void leerArchivo();

    
    
  
};