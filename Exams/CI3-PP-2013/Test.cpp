#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "ClubeVideo.h"

void test_a_existeCliente_existeFilme() {

	ClubeVideo vc;

	Cliente c1("Joao");
	Cliente c2("Maria");
	Cliente c3("Ana");
	Cliente c4("Pedro");

	vc.addCliente(c1);
	vc.addCliente(c2);
	vc.addCliente(c3);
	vc.addCliente(c4);

	ASSERT_EQUAL(true, vc.existeCliente("Pedro"));
	ASSERT_EQUAL(true, vc.existeCliente("Maria"));
	ASSERT_EQUAL(false, vc.existeCliente("Carlos"));
	ASSERT_EQUAL(false, vc.existeCliente("Andre"));

	Filme dvd1("Alcatraz");
	Filme dvd2("Al Capone");
	Filme dvd3("Big Bang Theory, The");
	Filme dvd4("Big Fish");
	Filme dvd5("Doctor Who");
	Filme dvd6("Man of Steel");
	Filme dvd7("Red Tails");
	Filme dvd8("Harry Potter");

	vc.addFilme(dvd1);
	vc.addFilme(dvd2);
	vc.addFilme(dvd3);
	vc.addFilme(dvd4);
	vc.addFilme(dvd5);
	vc.addFilme(dvd6);
	vc.addFilme(dvd7);
	vc.addFilme(dvd8);

	ASSERT_EQUAL(true, vc.existeFilme("Big Bang Theory, The"));
	ASSERT_EQUAL(true, vc.existeFilme("Red Tails"));
	ASSERT_EQUAL(true, vc.existeFilme("Doctor Who"));
	ASSERT_EQUAL(false, vc.existeFilme("True Lies"));
	ASSERT_EQUAL(false, vc.existeFilme("Spider-Man"));

	Cliente c5("Simao");   c5.addFilme( Filme("True Lies") );
	Cliente c6("Eduardo"); c6.addFilme( Filme("Spider-Man") );
	vc.addCliente(c5);
	vc.addCliente(c6);

	ASSERT_EQUAL(true, vc.existeFilme("True Lies"));
	ASSERT_EQUAL(true, vc.existeFilme("Spider-Man"));

}

void test_b_imprimirFilmes() {

	ClubeVideo vc1;

	vc1.addFilme( Filme("Harry Potter") );
	vc1.addFilme( Filme("Gladiator") );
	vc1.addFilme( Filme("Batman") );

	ASSERT_EQUAL("Harry Potter 0\nGladiator 0\nBatman 0\n", vc1.imprimirFilmes());

	ClubeVideo vc2;
	ASSERT_EQUAL("", vc2.imprimirFilmes());

	ClubeVideo vc3;
	Cliente c1("Antonio");
	Cliente c2("Elisabete");

	c1.addFilme( Filme("Dune") );
	c2.addFilme( Filme("Top Gun") );
	c2.addFilme( Filme("Godfather, The") );

	vc3.addCliente(c1);
	vc3.addCliente(c2);

	ASSERT_EQUAL("Dune 0\nGodfather, The 0\nTop Gun 0\n", vc3.imprimirFilmes());

}

void test_c_titulosDisponiveis() {

	ClubeVideo vc;
	list<string> ls = vc.titulosDisponiveis();

	ASSERT_EQUAL(0, ls.size());

	vc.addFilme( Filme("Harry Potter") );
	vc.addFilme( Filme("Gladiator") );
	vc.addFilme( Filme("Batman") );

	ls = vc.titulosDisponiveis();
	ASSERT_EQUAL(3, ls.size());

	vc.addFilme( Filme("Harry Potter") );
	vc.addFilme( Filme("Mozart") );

	ls = vc.titulosDisponiveis();
	ASSERT_EQUAL(4, ls.size());

	Cliente c("Pedro");
	c.addFilme( Filme("Gladiator") );
	c.addFilme( Filme("Internship, The") );
	vc.addCliente(c);

	ls = vc.titulosDisponiveis();
	ASSERT_EQUAL(4, ls.size());

	stringstream ss;
	for(list<string>::iterator itl = ls.begin(); itl != ls.end(); ++itl) {
		ss << (*itl) << "\n";
	}

	ASSERT_EQUAL("Batman\nGladiator\nHarry Potter\nMozart\n", ss.str());

}

void test_d_tituloDisponivel() {

	ClubeVideo vc;

	vc.addFilme( Filme("Harry Potter") );
	vc.addFilme( Filme("Gladiator") );
	vc.addFilme( Filme("Batman") );

	ASSERT_EQUAL(true, vc.tituloDisponivel("Gladiator"));
	ASSERT_EQUAL(true, vc.tituloDisponivel("Harry Potter"));
	ASSERT_EQUAL(false, vc.tituloDisponivel("Platoon"));

	vc.addFilme( Filme("Platoon") );
	ASSERT_EQUAL(true, vc.tituloDisponivel("Batman"));
	ASSERT_EQUAL(true, vc.tituloDisponivel("Platoon"));

	Cliente c1("Joao");
	c1.addFilme( Filme("We Were Soldiers") );
	vc.addCliente(c1);

	ASSERT_EQUAL(false, vc.tituloDisponivel("We Were Soldiers"));

}

void test_e_imprimirListaDeEspera() {

	ClubeVideo vc;

	vc.addPedidoCliente(PedidoCliente("Joao", "Gladiator"));
	vc.addPedidoCliente(PedidoCliente("Maria", "We were Soldiers"));
	vc.addPedidoCliente(PedidoCliente("Pedro", "Platoon"));

	string s1 = "Gladiator\nPlatoon\nWe were Soldiers\n";
	string s2 = vc.imprimirListaDeEspera();
	ASSERT_EQUAL(s1, s2);

	s2.erase( s2.find("Gladiator\n"), 10 );
	s2.erase( s2.find("We were Soldiers\n"), 17 );
	s2.erase( s2.find("Platoon\n"), 8 );

	ASSERT_EQUAL( 0, s2.size() );

}

void test_f_alugar() {

	ClubeVideo vc;

	vc.addFilme( Filme("Saving Private Ryan") );
	vc.addFilme( Filme("Band of Brothers") );
	vc.addFilme( Filme("Pacific, The") );
	ASSERT_EQUAL(3, vc.numFilmes());

	vc.addCliente( Cliente("Mateu") );
	vc.addCliente( Cliente("Ricardo") );
	ASSERT_EQUAL(2, vc.numClientes());

	vc.alugar("Mateu", "Band of Brothers");
	ASSERT_EQUAL(2, vc.numFilmes());
	ASSERT_EQUAL(0, vc.numPedidos());

	vc.alugar("Ana", "Pacific, The");
	ASSERT_EQUAL(1, vc.numFilmes());
	ASSERT_EQUAL(3, vc.numClientes());
	ASSERT_EQUAL(0, vc.numPedidos());

	vc.alugar("Pedro", "Pacific, The");
	ASSERT_EQUAL(1, vc.numFilmes());
	ASSERT_EQUAL(4, vc.numClientes());
	ASSERT_EQUAL(1, vc.numPedidos());

	vc.alugar("Wagner", "Band of Brothers");
	ASSERT_EQUAL(1, vc.numFilmes());
	ASSERT_EQUAL(5, vc.numClientes());
	ASSERT_EQUAL(2, vc.numPedidos());

	ASSERT_THROWS(vc.alugar("Pedro", "Platoon"), FilmeInexistente);
	try {
		vc.alugar("Pedro", "Platoon");
	}
	catch(FilmeInexistente& fie) {
		string str = fie.msg();
		ASSERT_EQUAL("Titulo Inexistente: Platoon", str);
	}

}

void test_g_devolver() {

	ClubeVideo vc;

	vc.addFilme( Filme("Saving Private Ryan") );
	vc.addFilme( Filme("Band of Brothers") );
	vc.addFilme( Filme("Pacific, The") );
	ASSERT_EQUAL(3, vc.numFilmes());
	ASSERT_EQUAL(0, vc.numClientes());
	ASSERT_EQUAL(0, vc.numPedidos());

	vc.alugar("Francisco", "Pacific, The");
	vc.alugar("Teresa", "Saving Private Ryan");
	vc.alugar("Bartolomeu", "Band of Brothers");
	ASSERT_EQUAL(0, vc.numFilmes());
	ASSERT_EQUAL(3, vc.numClientes());
	ASSERT_EQUAL(0, vc.numPedidos());

	vc.alugar("Francisco", "Band of Brothers");
	ASSERT_EQUAL(0, vc.numFilmes());
	ASSERT_EQUAL(1, vc.numPedidos());

	vc.devolver("Francisco", "Pacific, The");
	ASSERT_EQUAL(1, vc.numFilmes());
	ASSERT_EQUAL(1, vc.numPedidos());

	vc.devolver("Bartolomeu", "Band of Brothers");
	ASSERT_EQUAL(1, vc.numFilmes());
	ASSERT_EQUAL(0, vc.numPedidos());

}

void runSuite() {
	cute::suite s;
	s.push_back(CUTE(test_a_existeCliente_existeFilme));
	s.push_back(CUTE(test_b_imprimirFilmes));
	s.push_back(CUTE(test_c_titulosDisponiveis));
	s.push_back(CUTE(test_d_tituloDisponivel));
	s.push_back(CUTE(test_e_imprimirListaDeEspera));
	s.push_back(CUTE(test_f_alugar));
	s.push_back(CUTE(test_g_devolver));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main() {
    runSuite();
    return 0;
}



