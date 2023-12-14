#include <iostream>
#include <string>

using namespace std;

class Proceso {
private:
  string id;
  int arrivalTime;
  int cpuTime;
  int finTime;
  int esperaTime;
  int turnaroundTime;
  int sumaTiempos;
  int btSuplente; 

public:
  Proceso();
  Proceso(string id, int arrivalTime, int cpuTime);
  void setID(string newID);
  string getID();
  void setArrivalTime(int newTime);
  int getArrivalTime();
  void setCpuTime(int newCpuTime);
  int getCpuTime() const;
  void setFinTime(int newFinTime);
  int getFinTime();
  void setEsperaTime(int newEsperaTime);
  int getEsperaTime();
  void setTurnaroundTime(int newTT);
  int getTurnaroundTime();
  void quitarTiempo();
  void calcularMetricas();
  void sumarTiempos();
  int getSumTiempos() const;
  void setSumTiempos(int value);
  int getBtSuplente();
  void setBtSuplente(int value);
  
};