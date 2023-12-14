#include "Proceso.h"

Proceso::Proceso() {
  id = "default";
  arrivalTime = 0;
  cpuTime = 0;
  finTime = 0;
  turnaroundTime = 0;
  esperaTime = 0;
}

Proceso::Proceso(string newID, int newArrivalTime, int newCpuTime) {
  id = newID;
  arrivalTime = newArrivalTime;
  cpuTime = newCpuTime;
  finTime = 0;
  esperaTime = 0;
  turnaroundTime = 0;
  sumaTiempos = 0;
  btSuplente = newCpuTime;
  sumarTiempos();
}

void Proceso::setID(string newID) { id = newID; }

string Proceso::getID() { return id; }

void Proceso::setArrivalTime(int newTime) { arrivalTime = newTime; }

int Proceso::getArrivalTime() { return arrivalTime; }

void Proceso::setCpuTime(int newCpuTime) { cpuTime = newCpuTime; }

int Proceso::getCpuTime() const { return cpuTime; }

void Proceso::setFinTime(int newFinTime) { finTime = newFinTime; }

int Proceso::getFinTime() { return finTime; }

void Proceso::setEsperaTime(int newEsperaTime) { esperaTime = newEsperaTime; }

int Proceso::getEsperaTime() { return esperaTime; }

void Proceso::setTurnaroundTime(int newTT) { turnaroundTime = newTT; }

int Proceso::getTurnaroundTime() { return turnaroundTime; }

void Proceso::quitarTiempo() { cpuTime -= 1; }

void Proceso::sumarTiempos() { sumaTiempos = arrivalTime + cpuTime; }

int Proceso::getSumTiempos() const { return sumaTiempos; }
void Proceso::setSumTiempos(int value) { sumaTiempos = value; }

int Proceso::getBtSuplente() { 
  return btSuplente;
}
void Proceso::setBtSuplente(int value) { 
  btSuplente = value;
}