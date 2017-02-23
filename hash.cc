#include<iostream>
#include<vector>
using namespace std;
typedef int Int;
typedef float Float;

int v, e, r, c, x;
vector<Int> sizes;
vector< vector<Float> > endpoints;
vector<Float> datacenter_latencies;
vector< vector<Float> > caches;

int main() {
  // Lee los parámetros
  cin >> v >> e >> r >> c >> x;
  
  // Tamaños de los vídeos
  sizes = vector<Int>(v,0);
  for (int i=0; i<v; i++)
    cin >> sizes[i];
  
  // Endpoints
  endpoints = vector< vector<Float> >(e, vector<Float>(c,-1));
  for (int i=0; i<e; i++) {
    cin >> datacenter_latencies[i];
    int k; 
    cin >> k;
    for (int j=0; j<k; j++) {
      int index;
      cin >> index;
      cin >> endpoints[i][index];
    }
  }

  // Calcula molonosidad de cada vídeo en cada caché
  // Requests
  caches = vector< vector<Float> >(c,vector<Float>(v,0));
  for (int a=0; a<r; a++) {
    int video, endpoint, requests;
    cin >> video >> endpoint >> requests;

    // Para cada cache
    for (int i=0; i<c; i++) {
      // Si está conectado al endpoint
      if (endpoints[endpoint][i] != -1)
	// Calcula lo que molaría que este vídeo estuviera ahí
	caches[i][video] += requests*(datacenter_latencies[endpoint] - endpoints[endpoint][i]);
    }
  }

  // Elige los vídeos que va a usar, cogiendo los de más molonosidad
  // (?) Multiplica inversamente la molonosidad por el tamaño para elegir cuál usar
  cout << c << endl;
  
  for (int i=0; i<c; i++) {
    Int currentsize = 0;
    cout << i << ' ';
    
    // Métele vídeos
    while(true) {
      // Busca el vídeo más molón
      int maxindex = 0;
      int maxmolonosidad = caches[i][0];
      for (int j=0; j<v; j++) {
	if (caches[i][j] > maxmolonosidad) {
	  maxmolonosidad = caches[i][j];
	  maxindex = j;
	}
      }
      
      // Inserta el vídeo más molón y lo deja con cero de molonosidad
      currentsize += sizes[maxindex];
      caches[i][maxindex] = 0;

      // ¿Ha ido todo bien?
      if (currentsize > x) break; // No podemos meter más vídeos
      if (maxmolonosidad == 0) break; // Tampoco iban a aportar nada más
      
      // Lo escribe ya en output
      cout << maxindex << ' ';
    }

    cout << endl;
  }
}
