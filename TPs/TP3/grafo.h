#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

//Prototipos

template <class N, class A> class Aresta;

template <class N, class A> class No;

template <class N, class A> class Grafo;

template <class N> class ArestaRepetida;

template <class N> class NoRepetido;

template <class N> class NoInexistente;

template <class N> class ArestaInexistente;


//Declaracoes das classes

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};


template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};


template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};


//Metodos

template <class N, class A>
Grafo<N,A>::Grafo(){}

template <class N, class A>
Grafo<N,A>::~Grafo()
{
	for(int i=0;i<nos.size();++i)
		delete nos.at(i);
}


template <class N, class A>
int Grafo<N,A>::numNos(void) const
{
	return nos.size();
}


template <class N, class A>
int Grafo<N,A>::numArestas(void) const
{
	int count=0;

	for(int i=0;i<nos.size();++i)
		for(int j=0;j<nos.at(i)->arestas.size();++j)
			++count;

	return count;
}


template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirNo(const N &dados)
{
	for(int i=0;i<nos.size();++i)
		if(nos.at(i)->info==dados)
			throw NoRepetido<N>(dados);

		//Allocating a new No
		No<N, A> * temp_no = new No<N, A>(dados);
		//Pushing back to the vector
		nos.push_back(temp_no);

	return *this;
}


template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val)
{

	for(int i=0;i<nos.size();++i)
		if(nos.at(i)->info==inicio)
		{
			for(int j=0;j<nos.at(i)->arestas.size();++j)
				if(nos.at(i)->arestas.at(j).destino->info == fim)
					throw ArestaRepetida<N>(inicio,fim);

			No<N,A> *temp = new No<N,A>(fim);

			Aresta<N,A> a1(temp,val);
			nos.at(i)->arestas.push_back(a1);

			return *this;
		}

	throw NoInexistente<N>(inicio);
}


template <class N, class A>
A & Grafo<N,A>::valorAresta(const N &inicio, const N &fim)
{
	for(int i=0;i<nos.size();++i)
		if(nos.at(i)->info==inicio)
		{
			for(int j=0;j<nos.at(i)->arestas.size();++j)
				if(nos.at(i)->arestas.at(j).destino->info==fim)
					return nos.at(i)->arestas.at(j).valor;

			throw ArestaInexistente<N>(inicio,fim);
		}

	throw NoInexistente<N>(inicio);
}


template <class N, class A>
Grafo<N,A> & Grafo<N,A>::eliminarAresta(const N &inicio, const N &fim)
{
	for(int i=0;i<nos.size();++i)
			if(nos.at(i)->info==inicio)
			{
				for(int j=0;j<nos.at(i)->arestas.size();++j)
					if(nos.at(i)->arestas.at(j).destino->info==fim)
						{
							nos.at(i)->arestas.erase(nos.at(i)->arestas.begin()+i);
							return *this;
						}

				throw ArestaInexistente<N>(inicio,fim);
			}

		throw NoInexistente<N>(inicio);
}


template <class N, class A>
void Grafo<N,A>::imprimir(std::ostream &os) const
{
	for(int i=0;i<nos.size();++i)
	{
		os << "( " << nos.at(i)->info;

		for(int j=0;j<nos.at(i)->arestas.size();++j)
			os << " [" << nos.at(i)->arestas.at(j).destino->info << " " << nos.at(i)->arestas.at(j).valor << "]";

		os << " ) ";
	}
}


template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g)
{
	g.imprimir(out);

	return out;
}

// excecao  NoRepetido

template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};


template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente

template <class N>
class NoInexistente{
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};


template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }


//excecao ArestaRepetida

template <class N>
class ArestaRepetida
{
public:
	N inicio;
	N destino;
	ArestaRepetida(N inic, N dest) {
		inicio=inic;
		destino=dest; }
};


template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &aresta)
{
	out << "Aresta repetida: " << aresta.inicio << " , " << aresta.destino;
	return out;
}


//exceção ArestaInexistente

template <class N>
class ArestaInexistente
{
public:
	N inicio;
	N destino;
	ArestaInexistente(N inic, N dest) {
		inicio=inic;
		destino=dest; }
};


template <class N>
std::ostream & operator <<(std::ostream &out, const ArestaInexistente<N> &aresta)
{
	out << "Aresta inexistente: " << aresta.inicio << " , " << aresta.destino;
	return out;
}

