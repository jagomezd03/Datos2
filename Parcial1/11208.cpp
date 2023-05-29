#include <bits/stdc++.h>

using namespace std;

struct point
{
	int x, y;
};
point land_lst[110], queue_[110]; // Se crean los grafos

const int mod = 100007;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Definimos los limites del problema y variables para facilitarnos el problema
bool vis[11][11]; // Limites de filas y columnas
char api[13][13][10], ld[77][100];
int n, r, c, pos[2][222], value[13][13], cnt[222], vv, st[222], lst[44], qt[222], ans[44], at[2][222], mat[13][13], cnt_lst, ep[222], num[mod];
long long hash_[mod][107], big_mod = (long long)100000009 * (long long)100000009, ex[111];

// Definir el estado de la posicion
bool judge(int x, int y, int state)
{
	int i, j, s, p, q, vv, temp1, temp2, temp; // Inicializamos las variables
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
		{
			vis[i][j] = false; // Identificamos el arreglo a traves de las variable entregadas por usuario referentes a columnas y filas
		}
	queue_[0].x = x; // Almacena las coordenadas en X
	queue_[0].y = y; // Almacena las coordenadas en Y
	temp = 1; // Inicializa variable
	vis[x][y] = true; // Identifica los puntos en el arreglo
	temp1 = 0; // Inicializa Variable
	temp2 = 0; // Inicializar Variable
	while (temp1 <= temp2)
	{
		for (i = temp1; i <= temp2; i++)
		{
			for (j = 0; j < 4; j++)
			{
				x = queue_[i].x + dx[j]; // Almacena la coordenada X
				y = queue_[i].y + dy[j]; // Almacena la coordenada Y
				if (x >= 0 && x < r && y >= 0 && y < c && !vis[x][y])
				{
					vv = mat[x][y];
					if (api[x][y][0] != '#' && !(vv > 0 && api[x][y][0] >= '0' && api[x][y][0] <= '9' && state & (1 << vv))) // Condicional para eliminar los puntos muertos y los parqueaderos
					{
						queue_[temp].x = x; // Almacena coordenadas en X
						queue_[temp++].y = y; // Almacena coordenadas en Y
						if (api[x][y][0] == '=') // Condicional para identificar aterrizaje
						{
							return true;
						}
						vis[x][y] = true; // Almacena en el arreglo las coordenadas finales
					}
				}
			}
		}
		temp1 = temp2 + 1;
		temp2 = temp - 1;
	}
	return false;
}
// Lo creamos para saber donde ubicar
void bfs(point can_lst[], int &cnt_can, int id) // Identificar los espacios vacios y los espacios de despegue
{
	int i, j, s, p, q, x, y, temp1, temp2, temp;
	temp = 0; // Inicializamos la variable
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
		{
			vis[i][j] = false; // Identificamos el arreglo a traves de las variable entregadas por usuario referentes a columnas y filas
		}
	for (i = 0; i < cnt_lst; i++)
	{
		queue_[temp++] = land_lst[i]; // Almacenamos posiciones en el arreglo a traves del arreglo que contiene los sitios de despegue y aterrizaje
		vis[land_lst[i].x][land_lst[i].y] = true; // Identificamos las posiciones en las que no se podra parquear como true en el arreglo
	}
	temp1 = 0; // Inicializamos la variable
	temp2 = temp - 1; // Inicializamos la variable
	while (temp1 <= temp2)
	{
		for (i = temp1; i <= temp2; i++)
		{
			for (j = 0; j < 4; j++)
			{
				x = queue_[i].x + dx[j]; // Almacena en x la coordenada X del arreglo que contiene los sitios de despegue y aterrizaje
				y = queue_[i].y + dy[j]; // Almacena en y la coordenada Y del arreglo que contiene los sitios de despegue y aterrizaje
				if (x >= 0 && x < r && y >= 0 && y < c && !vis[x][y]) // Condicional para seleccionar las posiciones del arreglo sacando a los puntos de aterrizaje
				{
					if (api[x][y][0] != '#' && !(api[x][y][0] >= '0' && api[x][y][0] <= '9' && mat[x][y])) // Identificar los espacios vacios
					{
						queue_[temp].x = x; // Coordenasdas en X
						queue_[temp++].y = y; // Coordenadas en Y
						vis[x][y] = true;
						if (api[x][y][0] >= '0' && api[x][y][0] <= '9' && mat[x][y] == 0)
						{
							can_lst[cnt_can++] = queue_[temp - 1]; // Almaceno las coordenadas en el arreglo can_lst
						}
					}
				}
			}
		}
		temp1 = temp2 + 1; // Reasignamos valores hasta que se siga cumpliendo el condicional
		temp2 = temp - 1; // Reasignamos valores hasta que se siga cumpliendo el condicional
	}
}
// creamos para determinar si tiene salida
bool dfs(int id, int state, long long hs)
{
	int la, id_r, id_c, i, j, s, p, q, vv, nst, x, y, temp;
	long long nhs; // Inicializamos la variable
	bool res; // Inicializamos la variable que nos devuelve el resultado en uno de los mejores casos
	if (id >= 2 * n)
	{
		return true; // Condicion recursiva en el mejor de los casos
	}

	vv = lst[id]; // Almacena el valor de los operaciones
	cnt[vv] ^= 1; // Almacena su signo representado con 1 como positivo y 0 como negativo
	if (cnt[vv] == 0) //Ingresa al condicional cuando sea negativo osea una salida
	{
		id_r = at[0][vv]; // Almacena la coordenada de fila en el arreglo de la posicion solicitada temp
		id_c = at[1][vv]; // Almacena la coordenada de fila en el arreglo de la posicion solicitada temp

		at[0][vv] = at[1][vv] = -1; // Se reinicia el valor
		temp = mat[id_r][id_c]; // Se almacena temp el valor del arreglo en la posicion de la fila y columna
		while (temp == 0)
		{
			puts("orz"); //Excepcion que detiene la ejecucion debido a vacio
		}
		mat[id_r][id_c] = 0; // Libera esa coordenada
		nhs = hs - ex[value[id_r][id_c]];
		nhs = (nhs % big_mod + big_mod) % big_mod;
		res = dfs(id + 1, state ^ (1 << vv), nhs);
		cnt[vv] ^= 1; // Avanza
		mat[id_r][id_c] = temp; // Se reasigna el valor almacenado en temp
		at[0][vv] = id_r; // Se reasigna el valor guardado en el temp_r
		at[1][vv] = id_c; // Se reasigna el valor guardado en el temp_c
		return res; //Devuelve la reevaluacion de la funcion
	}
	point can_lst[101]; // Transforma el arreglo en una estructura
	int cnt_can = 0; // Inicializamos la funcion
	bfs(can_lst, cnt_can, id); // Llamamos a la funcion bfs enviamos el arreglo con las coordenadas de los puntos de aterrizaje el aux para ese arreglo y el id recursivo

	int ct = 0;
	for (i = id; i < 2 * n; i++) // Hasta que sea igual a el numero de operaciones
	{
		if (ld[i][0] == '+') // Este resultado da al codigo ascii de +, cualquier resultado diferente rompe el ciclo, con esto se identifican cuantos aviones
		{
			ct++;
		}
		else
		{
			break;
		}
	}
	nst = (state & st[vv]); // Inializamos variable, esto realiza un and entre estos dos valores los cuales deben dar 0 en todas las posiciones para dar valido de lo contrario dara falso

	int lst[22], cl = 0; //Re define la variable a la mitad de lenght original
	for (i = 1; i <= n; i++)
	{
		if (nst & (1 << i)) // Condicional para verificar
		{
			lst[cl++] = i; // Almacena en el arreglo el valor de i para identificar invalidez
		}
	}
	lst[cl++] = vv; // Almacena en el arreglo las operaciones
	for (i = 0; i < cnt_can && ct <= cnt_can; i++)
	{

		x = can_lst[i].x;
		y = can_lst[i].y;

		while (mat[x][y] != 0)
		{
			puts("orz"); //Excepcion para detener el codigo debido a vacio
		}
		mat[x][y] = vv; // Almacena las operaciones dentro del arreglo
		at[0][vv] = x; // Almacena la coordenada X en la operacion
		at[1][vv] = y; // Almacena la coordenada Y en la operacion
		nhs = hs + ex[value[x][y]]; // Calcula el hash de acuerdo al numero de bytes
		nhs %= big_mod; // Same
		ans[vv] = value[x][y]; // Guardamos las coordenadas en el arreglo final a entregar
		int jj;
		for (jj = 0; jj < cl; jj++)
		{
			j = lst[jj]; // Almacenamos las operaciones a realizar
			if (!judge(at[0][j], at[1][j], (state | (1 << vv)) & ep[j])) // Enviamos las coordenadas de los puntos, ademas que analizamos las operaciones y el ep[j] + 2^j con esto buscamos verificar las coordenadas de las posiciones
			{
				break;
			}
		}
		if (jj >= cl && dfs(id + 1, state | (1 << vv), nhs)) // Re evaluamos
		{
			return true;
		}
		mat[x][y] = 0; // Reiniciamos arreglo
		at[0][vv] = at[1][vv] = -1; // Reiniciamos coordenadas
	}
	cnt[vv] ^= 1; // Reiniciamos arreglo temp
	return false; // Reiniciamos funcion
}

// Creamos la funcion main
int main()
{
	int i, j, s, p, q, vv, tst = 0, ax; // Inicializamos variables a usar
	while (scanf("%d", &n) && n)
	{ // Pedimos el numero de casos y verificamos si se guardo el dato y si es valido
		scanf("%d%d", &r, &c); // Pedimos las filas y columnas
		tst++; // Aumentamos el valor de el numero de caso
		memset(pos, -1, sizeof(pos)); // Llenamos los espacios de memoria del arreglo pos
		cnt_lst = 0; // Inicializamos la variable que nos ayudara con las coordenadas de los puestso de aterrizaje
		ax = 0; //Inicializamos la variable que nos ayudara a guardar el valor maximo del numero del parqueadero
		for (i = 0; i < r; i++) // Filas
		{
			for (j = 0; j < c; j++) // Columnas
			{
				scanf("%s", api[i][j]);	// Se leen los espacios seleccionados en el aeropuerto y se guardan en una matriz de caracteres de 13*13 con longitud maxima de 10
				if (api[i][j][0] >= '0' && api[i][j][0] <= '9') // Almacenamos datos si son parqueaderos
				{
					value[i][j] = 10 * (api[i][j][0] - '0') + api[i][j][1] - '0'; // Se convierte el caracteres ingresado a enteros a traves de restar el codigo 0 de ASCII
					pos[0][value[i][j]] = i; //Guarda cuantos parqueaderos hay por fila
					pos[1][value[i][j]] = j; // Guarda cuantos parqueaderos hay por columna
					ax = max(ax, value[i][j]); // Se guarda el valor maximo de parqueadero
				}
				if (api[i][j][0] == '=') // Almacenamos los sitios por donde llegan y salen los aviones
				{
					land_lst[cnt_lst].x = i;   // Se almacena la coordenada x
					land_lst[cnt_lst++].y = j; // Se almacena la coordenada y
				}
			}
		}
		ex[0] = 1;
		for (i = 1; i <= ax + 1; i++)
		{
			ex[i] = (ex[i - 1] << 1) % big_mod; // 2^ax bytes
		}

		for (i = 0; i < 2 * n; i++)
		{
			scanf("%s", ld[i]); //Recibe los posiciones de la grid de aeropuerto
		}
		memset(st, 0, sizeof(st)); //Llena los espacios en memoria del arreglo
		memset(ep, 0, sizeof(ep)); //Llena los espacios en memoria del arreglo
		for (i = 0; i < 2 * n; i++)
		{
			vv = 0; //Inicializamos la variable que almacenara el orden de llegada y salida
			int len = strlen(ld[i]); //Almacena la longitud del arreglo de la grid de posiciones
			while (len >= 10 || len <= 1)
			{
				puts("orz"); //Excepcion para detener el codigo
			}
			for (j = 1; j < len; j++)
			{
				vv = 10 * vv + ld[i][j] - '0'; //Va almacenando el orden que se debe seguir para los llegadas y salidas
			}
			lst[i] = vv; //Guarda el valor en el arreglo
			while (vv <= 0 || vv > n)
			{
				puts("orz"); //Excepcion para detener el codigo
			}
			if (ld[i][0] == '-')
			{
				memset(cnt, 0, sizeof(cnt)); //Inicializamos la memoria del arreglo
				for (j = 0; j <= i; j++)
				{
					cnt[lst[j]] ^= 1; //Esto empieza a almacenar las salidas en orden, agarra ese numero y lo invierte a traves de un xor y agrega un valor mas al arreglo hasta
				}
				for (j = 1; j <= n; j++)
				{
					if (cnt[j]) // Tiene algo en esa posicion
					{
						st[j] |= (1 << vv); // valor almacenado mas 2^vv cada que cambia por salida
						ep[vv] |= (1 << j); // el valor almacenado mas 2^j por cada salida, el valor se restablece para cada salida
					}
				}
			}
		}
		memset(cnt, 0, sizeof(cnt)); // Reinicia la memoria del arreglo
		memset(mat, 0, sizeof(mat)); // Inicializa memoria del arreglo
		memset(at, -1, sizeof(at)); // Inicializa memoria del arreglo
		memset(num, 0, sizeof(num)); // Inicializa memoria del arreglo
		printf("Case %d: ", tst); //Empezamos a imprimir el numero de caso
		if (!dfs(0, 0, 0))
		{
			puts("No");
		}
		else
		{
			puts("Yes");
			for (i = 1; i <= n; i++)
			{
				if (i > 1)
				{
					putchar(' '); // Colocamos espaciado entre las coordenadas
				}
				if (ans[i] >= 10) // Esto cuando la coordenada es menor que 10
				{
					printf("%d", ans[i]);
				}
				else // Sino satisfacemos el formato del problema
				{
					printf("0%d", ans[i]);
				}
			}
			printf("\n"); // Salto de linea
		}
	}
	return 0;
}