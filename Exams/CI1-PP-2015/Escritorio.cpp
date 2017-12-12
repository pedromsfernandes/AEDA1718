#include "Escritorio.h"
#include <iostream>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }



//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }

Documento Documento::operator+(const Documento &d2) const
{
	int numPag;
	float pPr, pAm;

	numPag=numPaginas + d2.getNumPaginas();

	pPr=(pPreto*numPaginas + d2.getNumPaginas()*d2.getPercentagemPreto())/(numPaginas+d2.getNumPaginas());
	pAm=(pAmarelo*numPaginas + d2.getNumPaginas()*d2.getPercentagemAmarelo())/(numPaginas+d2.getNumPaginas());

	return Documento(numPag,pPr,pAm);
}
//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }

bool ImpressoraPB::imprime(Documento doc1)
{
	if(numPagImprimir<doc1.getNumPaginas())
		return false;

	numPagImprimir-=doc1.getNumPaginas();

	docsImpressos.push_back(doc1);

	return true;
}

bool ImpressoraPB::tonerBaixo()
{
	if(numPagImprimir<30)
		return true;

	return false;
}


//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo) return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}

bool ImpressoraCores::imprime(Documento doc1)
{
	if(numPagImprimirAmarelo < doc1.getNumPaginas()*doc1.getPercentagemAmarelo() ||numPagImprimirPreto < doc1.getNumPaginas()*doc1.getPercentagemPreto())
		return false;

	numPagImprimirAmarelo -=doc1.getNumPaginas()*doc1.getPercentagemAmarelo();
	numPagImprimirPreto -= doc1.getNumPaginas()*doc1.getPercentagemPreto();

	docsImpressos.push_back(doc1);

	return true;
}

bool ImpressoraCores::tonerBaixo()
{
	if(numPagImprimirPreto < 20 || numPagImprimirAmarelo < 20)
		return true;

	return false;
}

//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }

int Escritorio::numImpressorasSemResponsavel() const
{
	int counter=0;

	for(int i=0;i<funcionarios.size();++i)
		counter+=funcionarios.at(i).getImpressoras().size();

	return impressoras.size()-counter;

}

vector<Impressora *> Escritorio::retiraImpressoras(int ano1)
{
	vector<Impressora *> vec;

	for(int i=0;i<impressoras.size();i++)
		if(impressoras.at(i)->getAno()<ano1)
		{
			vec.push_back(impressoras.at(i));
			impressoras.erase(impressoras.begin()+i);
			i--;
		}

	return vec;
}

Impressora * Escritorio::imprimeDoc(Documento doc1) const
{
	for(int i=0;i<impressoras.size();++i)
		if(impressoras.at(i)->imprime(doc1))
			return impressoras.at(i);

	ImpressoraPB* i1 = new ImpressoraPB("inexistente",0,0);

	return i1;
}

vector<Impressora *> Escritorio::tonerBaixo() const
{
	vector<Impressora *> vec;

	for(int i=0;i<impressoras.size();++i)
		if(impressoras.at(i)->tonerBaixo())
			vec.push_back(impressoras.at(i));

	return vec;
}

string Escritorio::operator()(string impCode)
{
	for(int i=0;i<funcionarios.size();++i)
		for(int j=0;j<funcionarios.at(i).getImpressoras().size();++j)
			if(funcionarios.at(i).getImpressoras().at(j)->getCodigo()==impCode)
				return funcionarios.at(i).getCodigo();

	return "nulo";
}
