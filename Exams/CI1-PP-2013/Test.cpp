#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Condominio.h"

void test_a_Mensalidade() {
	 Apartamento a1(100, 3, "Rui");
	 Vivenda v1(100, 20, true, "Rui");

	ASSERT_EQUAL_DELTA(73, a1.mensalidade(),0.001);
	ASSERT_EQUAL_DELTA(82, v1.mensalidade(),0.001);
}

void test_b_MensalidadeProprietario() {
	ECondominio ec1;
	Urbanizacao u1("urbanizacao_1",1);
	Apartamento *a1 = new Apartamento(100, 3, "Rui");
	Vivenda *v1 = new Vivenda(100, 20, true, "Rui");
	u1.adicionaImovel(a1);
	u1.adicionaImovel(v1);
	ec1.adicionaUrbanizacao(u1);

	Urbanizacao u2("urbanizacao_2",2);
	Apartamento *aa = new Apartamento(100, 1, "Rui");
	Vivenda *va = new Vivenda(100, 20, true, "Joao");
	u2.adicionaImovel(aa);
	u2.adicionaImovel(va);
	ec1.adicionaUrbanizacao(u2);

	ASSERT_EQUAL_DELTA(226, ec1.mensalidadeDe("Rui"),0.001);
}

void test_c_RemoveUrbanizacoes() {
	ECondominio ec1;

	Urbanizacao u1("urbanizacao_1",1);
	ec1.adicionaUrbanizacao(u1);

	Urbanizacao u2("urbanizacao_2",2);
	Apartamento *a21 = new Apartamento(100, 3, "Joao", 1);
	Vivenda *v22 = new Vivenda(100, 20, true, "Vasco", 2);
	u2.adicionaImovel(a21);
	u2.adicionaImovel(v22);
	ec1.adicionaUrbanizacao(u2);

	Urbanizacao u3("urbanizacao_3",3);
	Apartamento *a31 = new Apartamento(100, 1, "Rui");
	Vivenda *v32 = new Vivenda(100, 20, true, "Jo�o");
	Vivenda *v33 = new Vivenda(100, 20, true, "Rui");
	u3.adicionaImovel(a31);
	u3.adicionaImovel(v32);
	u3.adicionaImovel(v33);
	ec1.adicionaUrbanizacao(u3);

	Urbanizacao u4("urbanizacao_4",4);
	Apartamento *a41 = new Apartamento(100, 1, "Rui");
	u4.adicionaImovel(a41);
	ec1.adicionaUrbanizacao(u4);

	Urbanizacao u5("urbanizacao_5",5);
	Apartamento *a51 = new Apartamento(100, 3, "Artur");
	Vivenda *v52 = new Vivenda(100, 20, true, "Vasco");
	u5.adicionaImovel(a51);
	u5.adicionaImovel(v52);
	ec1.adicionaUrbanizacao(u5);

	vector<Urbanizacao> v=ec1.removeUrbanizacaoDe("Rui");
	ASSERT_EQUAL(2, v.size());
	v=ec1.getUrbanizacoes();
	ASSERT_EQUAL(3, v.size());

	v=ec1.removeUrbanizacaoDe("Artur");
	ASSERT_EQUAL(1, v.size());
	v=ec1.getUrbanizacoes();
	ASSERT_EQUAL(2, v.size());
}


void test_d_AreaSuperiorA() {
	Urbanizacao u1("urbanizacao_1",3);

	vector<Imovel *> v=u1.areaSuperiorA(100);
	ASSERT_EQUAL(0,v.size());

	Vivenda *v1 = new Vivenda(100, 20, true, "Jo�o");
	Apartamento *a2 = new Apartamento(100, 1, "Rui");
	Vivenda *v3 = new Vivenda(100, 40, true, "Rui");
	u1.adicionaImovel(v1);
	u1.adicionaImovel(a2);
	u1.adicionaImovel(v3);
	v1->setID(1); a2->setID(2); v3->setID(3);

	v=u1.areaSuperiorA(135);
	ASSERT_EQUAL(1,v.size());
	ASSERT_EQUAL(3,v[0]->getID());

	v=u1.areaSuperiorA(110);
	ASSERT_EQUAL(2,v.size());

	v=u1.areaSuperiorA(200);
	ASSERT_EQUAL(0,v.size());
}



void test_e_OperadorMaior() {
	Urbanizacao u1("urbanizacao_1",1);
	Apartamento *a11 = new Apartamento(100, 3, "Joao");
	Vivenda *v12 = new Vivenda(100, 20, true, "Vasco");
	Vivenda *v13 = new Vivenda(100, 20, true, "Vasco");
	u1.adicionaImovel(a11);
	u1.adicionaImovel(v12);
	u1.adicionaImovel(v13);

	Urbanizacao u2("urbanizacao_2",2);
	Apartamento *a21 = new Apartamento(100, 1, "Rui");
	Vivenda *v22 = new Vivenda(100, 20, true, "Jo�o");
	Vivenda *v23 = new Vivenda(100, 20, true, "Jo�o");
	Vivenda *v24 = new Vivenda(100, 20, true, "Jo�o");
	u2.adicionaImovel(a21);
	u2.adicionaImovel(v22);
	u2.adicionaImovel(v23);
	u2.adicionaImovel(v24);

	ASSERT_EQUAL(true,u1>u2);


	Vivenda *v25 = new Vivenda(100, 20, true, "Ana");
	Vivenda *v26 = new Vivenda(100, 20, true, "Maria");
	Vivenda *v27 = new Vivenda(100, 20, true, "Clara");
	u2.adicionaImovel(v25);
	u2.adicionaImovel(v26);
	u2.adicionaImovel(v27);


	ASSERT_EQUAL(false,u1>u2);


	Urbanizacao u3("urbanizacao_3",3);
	ASSERT_EQUAL(true,u1>u3);
}


void test_f_OperadorFuncao() {
	ECondominio ec1;

	Urbanizacao u1("urbanizacao_1",1);
	ec1.adicionaUrbanizacao(u1);

	Urbanizacao u2("urbanizacao_2",2);
	Apartamento *a21 = new Apartamento(100, 3, "Joao");
	Vivenda *v22 = new Vivenda(100, 20, true, "Vasco");
	u2.adicionaImovel(a21);
	u2.adicionaImovel(v22);
	ec1.adicionaUrbanizacao(u2);

	Urbanizacao u3("urbanizacao_3",3);
	Apartamento *a31 = new Apartamento(100, 1, "Rui");
	Vivenda *v32 = new Vivenda(100, 20, true, "Jo�o");
	Vivenda *v33 = new Vivenda(100, 20, true, "Rui");
	u3.adicionaImovel(a31);
	u3.adicionaImovel(v32);
	u3.adicionaImovel(v33);
	ec1.adicionaUrbanizacao(u3);

	Urbanizacao u4("urbanizacao_4",4);
	Apartamento *a41 = new Apartamento(100, 1, "Rui");
	u4.adicionaImovel(a41);
	a41->setID(6);
	ec1.adicionaUrbanizacao(u4);

	vector<Imovel *> v=ec1("urbanizacao_1");
	ASSERT_EQUAL(0, v.size());

	v=ec1("urbanizacao_4");
	ASSERT_EQUAL(1, v.size());
	ASSERT_EQUAL(6,v[0]->getID());

	v=ec1("urbanizacao_3");
	ASSERT_EQUAL(3, v.size());

	v=ec1("urbanizacao_x");
	ASSERT_EQUAL(0, v.size());
}



void test_g1_IDSequencial() {
	Urbanizacao u1("urbanizacao_1");
	Apartamento *a11 = new Apartamento(100, 3, "Luis");
	Vivenda *v12 = new Vivenda(100, 20, true, "Vasco");
	u1.adicionaImovel(a11);
	u1.adicionaImovel(v12);

	Urbanizacao u2("urbanizacao_2");
	Apartamento *a21 = new Apartamento(100, 1, "Rui");
	Vivenda *v22 = new Vivenda(100, 20, true, "Jo�o");
	Vivenda *v23 = new Vivenda(100, 20, true, "Mario");
	u2.adicionaImovel(a21);
	u2.adicionaImovel(v22);
	u2.adicionaImovel(v23);

	Urbanizacao u3("urbanizacao_3");

	ASSERT_EQUAL(1,u1.getID());
	ASSERT_EQUAL(2,u2.getID());
	ASSERT_EQUAL(3,u3.getID());

	Urbanizacao::resetID();
	Urbanizacao u4("urbanizacao_4");
	ASSERT_EQUAL(1,u4.getID());
}

void test_g2_IDSequencial() {
	Urbanizacao::resetID();
	Urbanizacao u1("urbanizacao_1");
	Apartamento *a11 = new Apartamento(100, 3, "Luis");
	Vivenda *v12 = new Vivenda(100, 20, true, "Vasco");
	u1.adicionaImovel(a11);
	u1.adicionaImovel(v12);

	Urbanizacao u2("urbanizacao_2");
	Apartamento *a21 = new Apartamento(100, 1, "Rui");
	Vivenda *v22 = new Vivenda(100, 20, true, "Jo�o");
	Vivenda *v23 = new Vivenda(100, 20, true, "Mario");
	u2.adicionaImovel(a21);
	u2.adicionaImovel(v22);
	u2.adicionaImovel(v23);

	Urbanizacao u3("urbanizacao_3");

	ASSERT_EQUAL(1,u1.getID());
	ASSERT_EQUAL(2,u2.getID());
	ASSERT_EQUAL(3,u3.getID());

	ASSERT_EQUAL(1,a11->getID());
	ASSERT_EQUAL(2,v12->getID());
	ASSERT_EQUAL(1,a21->getID());
	ASSERT_EQUAL(2,v22->getID());
	ASSERT_EQUAL(3,v23->getID());
}



void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_a_Mensalidade));
	s.push_back(CUTE(test_b_MensalidadeProprietario));
	s.push_back(CUTE(test_c_RemoveUrbanizacoes));
	s.push_back(CUTE(test_d_AreaSuperiorA));
	s.push_back(CUTE(test_e_OperadorMaior));
	s.push_back(CUTE(test_f_OperadorFuncao));
	s.push_back(CUTE(test_g1_IDSequencial));
	s.push_back(CUTE(test_g2_IDSequencial));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "AEDA 2013/2014 - Avalia��o - 23/out - Testes Unitarios Estudantes");
}

int main(){
    runSuite();
    return 0;
}

