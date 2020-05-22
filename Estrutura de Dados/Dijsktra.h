int procuraMenorCaminho(flot *dist, int *visitado, int NV){
	int i, menor=-1, primeiro =1;
	for(i =0; i< NV; i++){
		if(dist[i] >= 0 && visitado[i] ==0){
			if(primeiro){
				menor =i;
				primeiro=0;
			}
			else{
				if(dist[menor] > dist[i])
					menor=i;
		}
	}
}
return menor;
}
void Dijsktra(Grafo *grafo , int ini , int *ant, float *dist){
	int i, cont , NV, ind, *visitado,u;
	cont=NV=gr->numero_vertice;
	visitado=(int *) malloc (NV * sizeof (int));
	for(i =0; i<NV; i++){
		ant[i]=-1;
		dist[i]=-1;
		visitado[i]=0;
	}
	dist[ini]=0;
	while(cont > 0){
		u=procuraMenorCaminho (dist,visitado,NV);
		if(u == -1)
			break;
		visitado[u] =1;
		cont--;
		for(i=0;i<gr->grau[u];i++){
			ind = gr->arestas[u][i];
			if(dist[ind] < 0){
				dist[ind] = dist[u]+1;
				ant[ind]=u;
			}else{
				if(dist[ind] > dist[u] +1){
					dist[ind] = dist[u] +1;
					ant[ind]=u;
				}
		}
		}
	}
	
	free(visitado);
		
}

int ant[m];
int dist[m];
Dijsktra(grafo, ant ,dist);