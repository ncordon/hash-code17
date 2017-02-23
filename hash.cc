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
vector< vector<Float> > videorequests;

int main() {
  // Lee los parámetros
  cin >> v >> e >> r >> c >> x;
  
  // Tamaños de los vídeos
  sizes = vector<Int>(v,0);
  for (int i=0; i<v; i++) {
    cin >> sizes[i];
  }
  
  // Endpoints
  datacenter_latencies = vector<Float>(e, 0);
  endpoints = vector< vector<Float> >(e, vector<Float>(c,-1));
  for (int i=0; i<e; i++) {
    // Su distancia al datacenter
    cin >> datacenter_latencies[i];
    // Está conectado a sólo k caches
    int k; cin >> k;
    
    for (int j=0; j<k; j++) {
      int index;
      cin >> index;
      cin >> endpoints[i][index];
    }
  }

  // Calcula molonosidad de cada vídeo en cada caché
  // Requests
  caches = vector< vector<Float> >(c,vector<Float>(v,0));
  videorequests = vector< vector<Float> >(e, vector<Float>(v,0));
  
  for (int a=0; a<r; a++) {
    int video, endpoint, requests;
    cin >> video >> endpoint >> requests;
    videorequests[endpoint][video] = requests;
    
    // Para cada cache
    for (int i=0; i<c; i++) {
      // Si está conectado al endpoint
      if (endpoints[endpoint][i] != -1)
	// Calcula lo que molaría que este vídeo estuviera ahí
	caches[i][video] += requests*(datacenter_latencies[endpoint] - endpoints[endpoint][i]);
    }
  }

  // Elige los vídeos que va a usar, cogiendo los de más molonosidad

  // OPTIMIZACIÓN 1
  // Multiplica inversamente la molonosidad por el tamaño para elegir cuál usar
  for (int i=0; i<c; i++)
    for (int j=0; j<v; j++)
      caches[i][j] *= (1.0 / sizes[j]);
  // OPTIMIZACIÓN 1

  
  cout << c << endl;

  // Para cada caché
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
      
      // Lo escribe ya en output y le quita molonosidad a meterlo en otras cachés
      cout << maxindex << ' ';

      
      // OPTIMIZACIÓN 2
      for (int b=0; b<c; b++) {
	for (int u=0; u<e; u++) {
	  if (b != i)
	    caches[b][maxindex] -= videorequests[u][maxindex] * (datacenter_latencies[u] - endpoints[u][i]);
	}
      }
      // ENDOPTIMIZACIÓN 2
    }

    cout << endl;
  }
}
