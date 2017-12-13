#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Cooperativa.h"

void test_a1_addVinhos() {

	Vinho v1("Cartuxa", 1998);
	Vinho v2("Quinta do Falcao", 1998);
	Vinho v3("Duas Quintas", 2005);
	Vinho v4("Fado", 2000);
	vector<Vinho> vv;
	vv.push_back(v1); vv.push_back(v2); vv.push_back(v3); vv.push_back(v4);

	Cooperativa c;
	c.addVinhos(vv);
	BST<Vinho> bst = c.getVinhos();
	BSTItrIn<Vinho> it(bst);

	ASSERT_EQUAL("Duas Quintas", it.retrieve().getNome());
	it.advance(); it.advance();
	ASSERT_EQUAL("Cartuxa", it.retrieve().getNome());
	it.advance();
	ASSERT_EQUAL("Quinta do Falcao", it.retrieve().getNome());

}

void test_a2_vinhosDisponiveis() {

	Vinho v1("Cartuxa", 1998);
	Vinho v2("Quinta do Falcao", 1998);
	Vinho v3("Duas Quintas", 2005);
	Vinho v4("Fado", 2000);
	Vinho v5("Alvarinho", 2002);
	Vinho v6("Redoma", 1999);
	Vinho v7("Duas Quintas", 2007);
	Vinho v8("Quinta do Falcao", 2008);
	Vinho v9("Fado", 2008);
	Vinho v10("Fado", 2011);
	Vinho v11("Cartuxa", 2001);
	Vinho v12("Alvarinho", 2008);
	vector<Vinho> vv;
	vv.push_back(v1); vv.push_back(v2); vv.push_back(v3);
	vv.push_back(v4); vv.push_back(v5); vv.push_back(v6);
	vv.push_back(v7); vv.push_back(v8); vv.push_back(v9);
	vv.push_back(v10); vv.push_back(v11); vv.push_back(v12);

	Cooperativa c;
	c.addVinho(v1); c.addVinho(v2); c.addVinho(v3); c.addVinho(v4);
	c.addVinho(v5); c.addVinho(v6); c.addVinho(v7); c.addVinho(v8);
	c.addVinho(v9); c.addVinho(v10); c.addVinho(v11); c.addVinho(v12);

	list<string> ls;
	list<string>::iterator its;

	ls = c.vinhosDisponiveis(2008, 2011);
	ASSERT_EQUAL(4, ls.size());
	its =ls.begin();
	ASSERT_EQUAL("Quinta do Falcao 2008",*its);
	its++; its++; its++;
	ASSERT_EQUAL("Alvarinho 2008",*its);

	ls = c.vinhosDisponiveis(2012, 2013);
	ASSERT_EQUAL(1, ls.size());

	its = ls.begin();
	ASSERT_EQUAL("Indisponivel", (*its));

	ls = c.vinhosDisponiveis(1998, 1998);
	ASSERT_EQUAL(2, ls.size());

	ls = c.vinhosDisponiveis(1900, 1997);
	ASSERT_EQUAL(1, ls.size());
	its = ls.begin();
	ASSERT_EQUAL("Indisponivel", (*its));

	ls = c.vinhosDisponiveis(1900, 2020);
	ASSERT_EQUAL(12, ls.size());

	its = ls.begin();
	ASSERT_EQUAL("Redoma 1999", (*its));

}

void test_a3_delVinhoNome() {

	Vinho v1("Cartuxa", 1998);
	Vinho v2("Quinta do Falcao", 1998);
	Vinho v3("Duas Quintas", 2005);
	Vinho v4("Fado", 2000);
	Vinho v5("Alvarinho", 2002);
	Vinho v6("Redoma", 1999);
	Vinho v7("Duas Quintas", 2007);
	Vinho v8("Quinta do Falcao", 2008);
	Vinho v9("Fado", 2008);
	Vinho v10("Fado", 2011);
	Vinho v11("Cartuxa", 2001);
	Vinho v12("Alvarinho", 2008);
	vector<Vinho> vv;
	vv.push_back(v1); vv.push_back(v2); vv.push_back(v3);
	vv.push_back(v4); vv.push_back(v5); vv.push_back(v6);
	vv.push_back(v7); vv.push_back(v8); vv.push_back(v9);
	vv.push_back(v10); vv.push_back(v11); vv.push_back(v12);

	Cooperativa c;
	c.addVinho(v1); c.addVinho(v2); c.addVinho(v3); c.addVinho(v4);
	c.addVinho(v5); c.addVinho(v6); c.addVinho(v7); c.addVinho(v8);
	c.addVinho(v9); c.addVinho(v10); c.addVinho(v11); c.addVinho(v12);

	ASSERT_EQUAL(3, c.delVinhoNome("Fado"));
	ASSERT_EQUAL(0, c.delVinhoNome("Monte Velho"));
	ASSERT_EQUAL(2, c.delVinhoNome("Alvarinho"));
	ASSERT_EQUAL(1, c.delVinhoNome("Redoma"));
	ASSERT_EQUAL(2, c.delVinhoNome("Cartuxa"));
	ASSERT_EQUAL(2, c.delVinhoNome("Quinta do Falcao"));
	ASSERT_EQUAL(2, c.delVinhoNome("Duas Quintas"));

	BST<Vinho> bst = c.getVinhos();
	ASSERT_EQUAL(true, bst.isEmpty());

}
void test_b1_addVinicola() {

	Cooperativa c;
	c.addVinicola("Quinta da Aveleda");
	c.addVinicola("Casa Agricola Quinta do Falcao");
	c.addVinicola("Sogrape Vinhos");

	hashVinicola hv = c.getVinicolas();
	ASSERT_EQUAL(3, hv.size());


	c.addVinicola("Casa Agricola Quinta do Falcao");
	c.addVinicola("Sogrape Vinhos");
	hv = c.getVinicolas();
	ASSERT_EQUAL(3, hv.size());

	c.addVinicola("Quinta da Aveleda");
	c.addVinicola("Herdade dos Coelheiros");
	hv = c.getVinicolas();
	ASSERT_EQUAL(4, hv.size());

	c.addVinicola("Herdade dos Coelheiros");
	ASSERT_EQUAL(4, hv.size());

	ASSERT_EQUAL(2,(c.getVinicolas().begin())->getVinhos());

}

void test_b2_maisOpcoes() {

	Cooperativa c;
	hashVinicola hv;

	Vinicola v1("Quinta da Aveleda");
	v1.setVinhos(1);
	Vinicola v2("Casa Agricola Quinta do Falcao");
	v2.setVinhos(1);
	Vinicola v3("Minha Quinta");
	v3.setVinhos(3);

	c.add_Vinicola(v1); c.add_Vinicola(v2);
	c.add_Vinicola(v3);
	hv=c.getVinicolas();
	ASSERT_EQUAL(3, hv.size());

	Vinicola vx=c.maisOpcoes();
	ASSERT_EQUAL("Minha Quinta",vx.getNome());

	Vinicola v4("Sogrape Vinhos");
	v4.setVinhos(3);
	c.add_Vinicola(v4);
	vx=c.maisOpcoes();
	ASSERT_EQUAL("Sogrape Vinhos",vx.getNome());

}


void test_c1_addEnologoVinicola() {

	Cooperativa c;

	c.addEnologoVinicola("Pedro", "Cartuxa");
	ASSERT_EQUAL(1, c.getEnologos().size());

	c.addEnologoVinicola("Americo", "Casal Bom");
	c.addEnologoVinicola("Pedro", "Herdade do Mar");
	ASSERT_EQUAL(2, c.getEnologos().size());
	ASSERT_EQUAL("Pedro", c.getEnologos().top().getNome());

	c.addEnologoVinicola("Antonio", "Esteva");
	c.addEnologoVinicola("Americo", "Herdade do Sol");
	c.addEnologoVinicola("Americo", "Herdade do Sol");
	c.addEnologoVinicola("Americo", "Herdade do Sol");
	ASSERT_EQUAL(3, c.getEnologos().size());
	ASSERT_EQUAL("Americo", c.getEnologos().top().getNome());

}

void test_c2_vinicolasMelhoresNEnologos() {

	Cooperativa c;

	ASSERT_EQUAL(0, c.vinicolasMelhoresNEnologos(2).size());

	Vinicola v1("Adega Jose de Sousa");
	v1.setVinhos(2);
	Vinicola v2("Casa Agricola Quinta do Falcao");
	v2.setVinhos(1);
	Vinicola v3("Sogrape Vinhos");
	v3.setVinhos(1);
	Vinicola v4("Herdade da Lapa");
	v4.setVinhos(1);
	Vinicola v5("Quinta da Granja");
	v5.setVinhos(1);

	Enologo e1("Pedro");
	Enologo e2("Joao");
	Enologo e3("Antonio");

	e1.addVinicolaInexistente(v1);
	e1.addVinicolaInexistente(v4);
	e2.addVinicolaInexistente(v5);
	e2.addVinicolaInexistente(v2);
	e3.addVinicolaInexistente(v3);

	c.addEnologo(e1);
	c.addEnologo(e2);
	c.addEnologo(e3);

	ASSERT_EQUAL(4, c.vinicolasMelhoresNEnologos(2).size());
	ASSERT_EQUAL(5, c.vinicolasMelhoresNEnologos(10).size());
	ASSERT_EQUAL(2, c.vinicolasMelhoresNEnologos(1).size());



	Vinicola v6("Quinta da Coruja");
	v6.setVinhos(5);
	Enologo e4("Luis");
	e4.addVinicolaInexistente(v6);
	c.addEnologo(e4);
	list<Vinicola> lv=c.vinicolasMelhoresNEnologos(1);
	ASSERT_EQUAL(1, lv.size());
	ASSERT_EQUAL("Quinta da Coruja", (lv.begin())->getNome());

}



void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(test_a1_addVinhos));
	s.push_back(CUTE(test_a2_vinhosDisponiveis));
	s.push_back(CUTE(test_a3_delVinhoNome));
	s.push_back(CUTE(test_b1_addVinicola));
	s.push_back(CUTE(test_b2_maisOpcoes));
	s.push_back(CUTE(test_c1_addEnologoVinicola));
	s.push_back(CUTE(test_c2_vinicolasMelhoresNEnologos));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "The Suite");
}


int main(){
    runSuite();
    return 0;
}



