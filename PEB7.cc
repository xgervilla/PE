#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
using namespace std;


//breadth first search
bool BFS(const vector<int>& v,int& centinela){
    int n = v.size();
    for(int i = 0; i<n; ++i){
        if(v[i] == centinela) return true;
    }
    return false;
}

//depth first search
bool DFS(const vector<int>& v, int& centinela, int& position){
    if(v[position] == centinela) return true;
    if(2*position<v.size()){
        int aux_esq = 2*position;
        int aux_dre = 2*position+1;
        return( DFS(v,centinela,aux_esq) or DFS(v,centinela,aux_dre) );
    }
    else return false;
}

int main(){
    //consideramos 3 vectores para los diferentes datos que nos interesan, 100 datos diferentes por ejecucion
    vector<double> Vdfs(100);
    vector<double> Vbfs(100);
    vector<double> tam(100);
    //semilla para los numeros aleatorios
    srand(time(NULL));
    for(int k = 0; k<100; ++k){

    //primero cogemos un size aleatorio para el vector (rango:: minimo +(rand()%(maximo-minimo+1))) -> hay que cambiar minimo y (maximo-minimo+1) segun el intervalo
    tam[k] = 500000+(rand()%(1000000-500000+1));
    int size = tam[k];

    //posicion aleatoria, entre 1 y el maximo, donde insertar el elemento "infiltrado"; como todos son naturales buscamos el único negativo, porque no se puede asegurar que no haya elementos (positivos) repetidos, asi que para evitar encontrar elementos en nodos diferentes que sean validos, buscamos un nodo (aleatorio) con nuestro centinela (-1)
    int pos = 1+(rand()%(1000000+1-1));
    while(pos>size) pos=1+(rand()%(1000000));
    //aseguramos que sea una posición válida (podríamos obtener un numero aleatorio mayor al que hemos obtenido como size)
    int centinela = -1;

    //vector que representa un árbol: respecto una posición i; padre en i/2; hijo izquierdo en 2*i; hijo derecho en 2*i+1 -> para que sea efectivo, v[0] no se tiene en cuenta (la llamada empieza en v[1]== v[pos_inicial])
    int pos_inicial = 1;
    vector<int> v(size);
    for(int i = 1; i<size; ++i){
        if(i == pos) v[i] = centinela;
        else v[i] = rand();
        //si la posicion en la que estamos es la interesada para colocar el centinela, lo "infiltramos", sino añadimos un natural aleatorio
    }

    //devolveremos un bool para comprobar que efectivamente encuentra el nodo
    bool found_bfs=false,found_dfs=false;

    //aleatorizamos el acceso a los algoritmos para maximizar la independencia 
    int orden = rand()%2;
    if(orden==1){
        //Primero se ejecuta BFS, a continuación DFS:

        //iniciamos el tiempo al momento actual, ejecutamos e iniciamos el tiempo al momento despues de finalizar
        auto b0=std::chrono::high_resolution_clock::now();
        found_bfs = BFS(v,centinela);
        auto b1=std::chrono::high_resolution_clock::now();

        //iniciamos el tiempo al momento actual, ejecutamos e iniciamos el tiempo al momento despues de finalizar
        auto d0=std::chrono::high_resolution_clock::now();
        found_dfs = DFS(v,centinela,pos_inicial);
        auto d1 = std::chrono::high_resolution_clock::now();

        //la duracion de los algoritmos es la diferencia entre el momento que se inicia la ejecución y que acaba
        double duration_bfs = std::chrono::duration_cast<std::chrono::nanoseconds>(b1-b0).count();

        Vbfs[k] = duration_bfs; //guardamos el tiempo en el vector para imprimirlo al final

        //la duracion de los algoritmos es la diferencia entre el momento que se inicia la ejecución y que acaba
        double duration_dfs = std::chrono::duration_cast<std::chrono::nanoseconds>(d1-d0).count();
        Vdfs[k] = duration_dfs; //guardamos el tiempo en el vector para imprimirlo al final

        //en caso de no encontrarlo saltaría error, lo cual no debe pasar si los intervalos estan bien hechos
        if(not (found_dfs and found_bfs)) cout << "Error al encontrar el centinela" << endl;
    }
    else{
        //Primero se ejecuta DFS, a continuación BFS:

        //iniciamos el tiempo al momento actual, ejecutamos e iniciamos el tiempo al momento despues de finalizar
        auto d0=std::chrono::high_resolution_clock::now();
        found_dfs = DFS(v,centinela,pos_inicial);
        auto d1 = std::chrono::high_resolution_clock::now();

        //iniciamos el tiempo al momento actual, ejecutamos e iniciamos el tiempo al momento despues de finalizar
        auto b0=std::chrono::high_resolution_clock::now();
        found_bfs = BFS(v,centinela);
        auto b1=std::chrono::high_resolution_clock::now();

        //la duracion de los algoritmos es la diferencia entre el momento que se inicia la ejecución y que acaba
        double duration_dfs = std::chrono::duration_cast<std::chrono::nanoseconds>(d1-d0).count();
        
        Vdfs[k] = duration_dfs; //guardamos el tiempo en el vector para imprimirlo al final

        //la duracion de los algoritmos es la diferencia entre el momento que se inicia la ejecución y que acaba
        double duration_bfs = std::chrono::duration_cast<std::chrono::nanoseconds>(b1-b0).count();
        Vbfs[k] = duration_bfs; //guardamos el tiempo en el vector para imprimirlo al final
        
        //en caso de no encontrarlo saltaría error, lo cual no debe pasar si los intervalos estan bien hechos
        if(not (found_dfs and found_bfs)) cout << "Error al encontrar el centinela" << endl;
    }
    }
    //imprimimos por filas el tiempo en bfs, dfs y el tamaño; al hacerlo asi mantenemos el emparejamiento
    cout << "BFS:   DFS:    N:" << endl;
    for(int m = 0;m<100;++m){
        cout << Vbfs[m] << ' ' << Vdfs[m] << ' ' << tam[m] << endl;
    }
    cout << endl;
}