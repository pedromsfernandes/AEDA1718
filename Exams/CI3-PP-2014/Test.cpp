#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Supermercado.h"

void test_a_NumeroValorItens() {

	Item i1(5, 2, 2, "uva", "fruta");
	Item i2(10, 1, 1, "dentifico", "higiene");
	Item i3(7, 3, 3, "detergente", "limpeza");

	vector<Item> v1;
	v1.push_back(i1);
	v1.push_back(i2);
	v1.push_back(i3);
	Cesto c1(v1);
	Cliente joao("Joao", 30);
	joao.addCesto(c1);

	Item i4(10, 1, 1, "coca-cola", "bebida");
	Item i5(7, 3, 3, "arroz", "grao");

	vector<Item> v2;
	v2.push_back(i4);
	v2.push_back(i5);
	Cesto c2(v2);
	joao.addCesto(c2);

	ASSERT_EQUAL(5, joao.numeroItens());
	ASSERT_EQUAL(39, joao.valorItens());

}

void test_b_trocarItem() {

	Item maca(1, 1, 1, "maca", "fruta");
	Item arroz(2, 1, 1, "arroz", "grao");
	Item lixivia(3, 2, 2, "lixivia", "limpeza");
	Item shampoo(5, 2, 2, "shampoo", "higiene");
	Item dentifico(2, 1, 1, "dentifico", "higiene");

	vector<Item> itens;
	itens.push_back(maca);
	itens.push_back(arroz);
	itens.push_back(lixivia);
	itens.push_back(shampoo);
	itens.push_back(dentifico);

	Cesto c1(itens);
	Cesto c2(itens);
	Item shampoo3(4, 2, 2, "shampoo", "higiene");
	c2.pushItem(shampoo3);

	Cliente joao("Joao", 25);
	joao.addCesto(c1);
	joao.addCesto(c2);

	Item shampooBarato(3, 2, 2, "shampoo", "higiene");

	ASSERT_EQUAL(3, joao.trocarItem(shampooBarato));

}

void test_c_organizarCestos() {

	Item i1(1, 1, 100, "melancia", "fruta");
	Item i2(1, 1, 60, "melao", "fruta");
	Item i3(1, 1, 20, "maca", "fruta");
	Item i4(1, 1, 50, "laranja", "fruta");
	Item i5(1, 1, 10, "uva", "fruta");

	Cesto c;

	c.pushItem(i2);
	c.pushItem(i3);
	c.pushItem(i1);
	c.pushItem(i4);
	c.pushItem(i5);

	Cliente joao("Joao", 25);
	joao.addCesto(c);

	joao.organizarCestos();
	list<Cesto> cs = joao.getCestos();
	list<Cesto>::iterator it = cs.begin();
	stack<Item> temp = (*it).getItens();

	ASSERT_EQUAL(10, temp.top().peso);
	temp.pop();
	ASSERT_EQUAL(20, temp.top().peso);
	temp.pop();
	ASSERT_EQUAL(50, temp.top().peso);
	temp.pop();
	ASSERT_EQUAL(60, temp.top().peso);
	temp.pop();
	ASSERT_EQUAL(100, temp.top().peso);
	temp.pop();

}

void test_d_contarTiposItens() {

	Item maca(1, 1, 1, "maca", "fruta");
	Item arroz(2, 1, 1, "arroz", "grao");
	Item lixivia(3, 2, 2, "lixivia", "limpeza");
	Item shampoo(5, 2, 2, "shampoo", "higiene");
	Item dentifico(2, 1, 1, "dentifico", "higiene");

	vector<Item> itens;
	itens.push_back(maca);
	itens.push_back(arroz);
	itens.push_back(lixivia);
	itens.push_back(shampoo);
	itens.push_back(dentifico);

	Cesto c1(itens);
	Cesto c2(itens);
	Item shampoo3(1, 2, 2, "shampoo", "higiene");
	c2.pushItem(shampoo3);

	Cliente joao("Joao", 25);

	joao.addCesto(c1);
	joao.addCesto(c2);

	vector<string> contagens = joao.contarItensPorTipo();
	ASSERT_EQUAL(4, joao.contarItensPorTipo().size());

	vector<string>::iterator it;
	it = find(contagens.begin(), contagens.end(), "higiene 5");

	ASSERT_EQUAL(it != contagens.end(), true);

}

void test_e_novoItem() {

	Item i1(1, 3, 3, "melancia", "fruta");
	Item i2(1, 3, 3, "melao", "fruta");
	Item i3(1, 3, 3, "maca", "fruta");
	Item i4(1, 3, 3, "laranja", "fruta");
	Item i5(1, 3, 3, "uva", "fruta");

	Cesto c;

	ASSERT_EQUAL(1, c.novoItem(i1));
	ASSERT_EQUAL(2, c.novoItem(i2));
	ASSERT_EQUAL(3, c.novoItem(i3));
	ASSERT_EQUAL(0, c.novoItem(i4));

	Cliente joao("Joao", 25);

	joao.addCesto(c);

	ASSERT_EQUAL(2, joao.novoItem(i4));

}

void test_f_novoCliente() {

	Supermercado jumbo;
	Item i1(1, 3, 3, "melancia", "fruta");
	Item i2(1, 3, 3, "melao", "fruta");
	Item i3(1, 3, 3, "maca", "fruta");
	Item i4(1, 3, 3, "laranja", "fruta");
	Item i5(1, 3, 3, "uva", "fruta");

	Cesto c;
	c.pushItem(i1);
	c.pushItem(i2);
	c.pushItem(i3);
	c.pushItem(i4);
	c.pushItem(i5);

	Cliente joao("Joao", 25);
	joao.addCesto(c);
	ASSERT_EQUAL(1, jumbo.novoCliente(joao));

	Cliente maria("Maria", 70);
	maria.addCesto(c);
	ASSERT_EQUAL(2, jumbo.novoCliente(maria));

	Cliente pedro("Pedro", 85);
	maria.addCesto(c);
	ASSERT_EQUAL(3, jumbo.novoCliente(pedro));
	ASSERT_EQUAL(1, jumbo.tamanhoFilaNormal());
	ASSERT_EQUAL(2, jumbo.tamanhoFilaPrioritaria());

	Cliente joana("Joana", 65);
	maria.addCesto(c);
	ASSERT_EQUAL(4, jumbo.novoCliente(joana));
	ASSERT_EQUAL(2, jumbo.tamanhoFilaNormal());

}

void test_g_sairDaFila() {
	Cliente joao("Joao", 30);
	Cliente maria("Maria", 10);
	Cliente ana("Ana", 72);
	Cliente rui("Rui", 20);
	Cliente vasco("Vasco", 18);
	Supermercado jumbo;

	queue<Cliente> fn;
	fn.push(joao);
	fn.push(rui);
	fn.push(maria);
	fn.push(vasco);

	queue<Cliente> fp;
	fp.push(ana);

	jumbo.setFilaNormal(fn);
	jumbo.setFilaPrioritaria(fp);



	ASSERT_THROWS(jumbo.sairDaFila("Ricardo"), Supermercado::ClienteInexistente);
	try {
			jumbo.sairDaFila("Ricardo");
	}
	catch (Supermercado::ClienteInexistente &e) {
			cout << "Apanhou excecao. Cliente nao existe: " << e.getNome() << endl;
			ASSERT_EQUAL("Ricardo", e.getNome());
	}

	Cliente c1=jumbo.sairDaFila("Rui");
	ASSERT_EQUAL("Rui",c1.getNome());
	ASSERT_EQUAL(3,jumbo.tamanhoFilaNormal());
	ASSERT_EQUAL("Joao",jumbo.getFilaNormal().front().getNome());

	c1=jumbo.sairDaFila("Vasco");
	ASSERT_EQUAL("Vasco",c1.getNome());
	ASSERT_EQUAL(2,jumbo.tamanhoFilaNormal());
	ASSERT_EQUAL("Joao",jumbo.getFilaNormal().front().getNome());

	c1=jumbo.sairDaFila("Ana");
	ASSERT_EQUAL("Ana",c1.getNome());
	ASSERT_EQUAL(0,jumbo.tamanhoFilaPrioritaria());

}

void thisIsATest() {
	ASSERTM("start writing tests", false);	
}

void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(test_a_NumeroValorItens));
	s.push_back(CUTE(test_b_trocarItem));
	s.push_back(CUTE(test_c_organizarCestos));
	s.push_back(CUTE(test_d_contarTiposItens));
	s.push_back(CUTE(test_e_novoItem));
	s.push_back(CUTE(test_f_novoCliente));
	s.push_back(CUTE(test_g_sairDaFila));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
    return 0;
}



