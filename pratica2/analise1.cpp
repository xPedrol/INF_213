
// Exemplo de analise de complexidade:
// Note que simplificamos ao máximo na notacao O (removendo o n, ja que O(n^2 +n) = O(n^2), pois a parte quadratica "pesa mais")
// Complexidade: O(n^2 + m + n) = O(n^2 + m)
void funcao1(int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ct *= j;

	for (int k = 0; k < m; k++)
		ct += 10;

	for (int k = 0; k < n; k++)
		ct += 10;
}

// Complexidade: O(n^2 + m^3 + k^3) = O(m^3 + k^3)
void funcao2(int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ct *= j;

	for (int k = 0; k < m; k++)
		funcao1(30, 40);

	for (int k = 0; k < n; k++)
		funcao1(n, 200);
}
// Complexidade: O(n*k + m/100000) = O(n*k)
void funcao3(int n, int m, int k)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < k; j++)
			ct *= m;

	for (int i = 0; i < m / 100000; i++)
	{
		ct += k;
	}
}

// Complexidade: O(n^2)
void funcao4(int n, int m, int k, int v[])
{
	int ct = 0;
	for (int i = 0; i < n; i++)
	{
		if (v[i] % 2 == 0)
			break;
		for (int j = 0; j < n; j++)
		{
			ct += v[i] + v[j];
		}
	}
}
// Complexidade: O(n^2)
void funcao5(int n, int m, int k, int v[])
{
	int ct = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ct++;
			if (ct % 2 == 0)
				break;
		}
	}
}
// Complexidade: O(n^2 * n) = O(n^3)
void funcao6(int n, int m, int k, int v[])
{
	int ct = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ct += log(n);
		}
	}
}
// Complexidade: O(n^2 * n) = O(n^3)
void funcao7(int n, int m, int k, int v[])
{
	int ct = 0;
	for (int i = 1; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			ct += log(n);
		}
	}
}
// Complexidade: O(n * log(m) * k)
void funcao8(int n, int m, int k, int v[])
{
	int ct = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < log(m); j++)
		{
			ct += sin(k);
		}
	}
}

// Responda (alem de analisar a complexidade): o que essa funcao faz?
// Complexidade: A complexidade do pior caso seria O(infinito)
// Resposta: teoricamente essa função deveria contar quantos digitos tem o numero n, mas ela não funciona para todos os casos
// pois se n for 0, ela retorna 0, mas 0 tem 1 digito
// alem de que caso o número não seja inteiro ou multiplo de 10, entrarão em loop infinito
void funcao9(int n)
{
	if (n == 0)
		return 0;
	return funcao9(n / 10) + 1;
}
// Complexidade: A complexidade do pior caso seria O(infinito)
void funcao10(int n, int m, int k, int v[])
{
	if (n == 0 && m == 0)
		return 1;
	if (n == 0)
		return funcao10(n, m / 2, k, v);
	else
		return funcao10(n / 2, m, k, v);
}
// Complexidade: O(n*v[i])
void funcao11(int n, int m, int k, int v[])
{
	int ct = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < v[i]; j++)
		{
			ct += k;
		}
	}
}
// Complexidade: O(n^3)
int funcao12(int n)
{
	int ans = 0;
	for (int i = 5; i < n; i++)
		for (int j = 3; j < n; j++)
			for (int k = 1; k < n; k++)
			{
				ans += 2;
				if (ans % 10 == 0)
					break;
			}
	return ans;
}
// Complexidade: não sei dizer
double funcao13(int v, int u, int f)
{
	double ans = 0;
	for (int i = 0; i < u; i++)
	{
		for (int j = 0; j < v; j++)
			ans -= log(i * j);
		ans += log(u + i);
		for (int j2 = 0; j2 < f / 2; j2++)
			for (int k = v / 2; k < v; k++)
				ans += log(j2 * k);
	}
	return ans;
}

// Analise a complexidade de melhor e pior caso dessa função
// Diga não apenas a complexidade, mas também explique quando esses tempos ocorrem
// Complexidade do pior caso: O(n) - Acontece quando o elemento procurado não está no vetor
// Complexidade do melhor caso: O(1) - Acontece quando o elemento procurado está na primeira posição do vetor
void funcao14(int n, int m, int k, int v[])
{
	int ct = 0;
	for (int i = 0; i < n; i++)
	{
		if (v[i] == m)
			return i;
	}
	return -1;
}

// Analise a complexidade de melhor e pior caso dessa função
// Diga não apenas a complexidade, mas também explique quando esses tempos ocorrem
// Complexidade do pior caso: O(infinito) - Acontece quando w é um número impar
// Complexidade do melhor caso: O(1) - Acontece quando w é um número par
int funcao15(int n, int w)
{
	int ans = w;
	for (int i = 5; i < n; i++)
		for (int j = 3; j < n; j++)
			for (int k = 1; k < n; k++)
			{
				ans += 2;
				if (ans % 10 == 0)
					break;
			}
	return ans;
}
// Complexidade: O(n/2*m)
int funcao16(int n, int w, int m)
{
	double ans = w;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; n--)
			for (int k = 0; k < m; k++)
				ans += 3.14;

	return ans;
}
