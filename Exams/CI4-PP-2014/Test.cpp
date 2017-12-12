#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Clinica.h"

void test_a1_addConsultas() {

 	Clinica cli;

	Consulta c1(2,10,3);
	Consulta c2(3,2,3);
	Consulta c3(4,10,3);
	Consulta c4(3,2,3);
	Consulta c5(4,20,2);

	vector<Consulta> vc;
	vc.push_back(c1);
	vc.push_back(c2);
	vc.push_back(c3);
	vc.push_back(c4);
	vc.push_back(c5);

	cli.addConsultas(vc,"Raul Santos");
	list<ConsultasVet> cv=cli.getConsultasDisponiveis();
	ASSERT_EQUAL(1,cv.size());
	BST<Consulta> consultasV=cv.front().minhasConsultas;

	Consulta consulta1=consultasV.findMin();
	ASSERT_EQUAL(2,consulta1.getMes());
	consultasV.remove(consulta1);
	consulta1=consultasV.findMin();
	ASSERT_EQUAL(3,consulta1.getMes());
	ASSERT_EQUAL(2,consulta1.getDia());
	consultasV.remove(consulta1);
	consulta1=consultasV.findMin();
	ASSERT_EQUAL(3,consulta1.getMes());
	ASSERT_EQUAL(10,consulta1.getDia());
	ASSERT_EQUAL(2,consulta1.getHora());
	consultasV.remove(consulta1);
	consulta1=consultasV.findMin();
	ASSERT_EQUAL(10,consulta1.getDia());
	ASSERT_EQUAL(4,consulta1.getHora());
	consultasV.remove(consulta1);
	ASSERT_EQUAL(true,consultasV.isEmpty());

	vc.clear();
	vc.push_back(c1);
    vc.push_back(c2);

    cli.addConsultas(vc,"Maria Dinis");
    cv=cli.getConsultasDisponiveis();
    ASSERT_EQUAL(2,cv.size());
    ASSERT_EQUAL("Maria Dinis",cv.front().nomeVeterinario);

}

void test_a2_veConsultasDisponiveis() {

	Clinica cli;

	Consulta c1(2,10,3);
	Consulta c2(3,2,3);
	Consulta c3(4,10,3);
	Consulta c4(3,5,3);
	Consulta c5(4,20,2);

	ConsultasVet vet1("Raul Santos");
	vet1.addConsulta(c1);
	vet1.addConsulta(c2);
	vet1.addConsulta(c3);
	vet1.addConsulta(c4);
	vet1.addConsulta(c5);
	ConsultasVet vet2("Maria Dinis");
	ConsultasVet vet3("Jaime Luis");
	vet3.addConsulta(c1);
	vet3.addConsulta(c2);
	vet3.addConsulta(c3);

	cli.addConsultasDisponiveisVet(vet1);
	cli.addConsultasDisponiveisVet(vet2);
	cli.addConsultasDisponiveisVet(vet3);

	list<Consulta> res;

	res = cli.veConsultasDisponiveis(1,12,3,"Raul Santos");
	ASSERT_EQUAL(4,res.size());
	ASSERT_EQUAL(2,res.front().getDia());
	ASSERT_EQUAL(4,res.back().getHora());
	ASSERT_EQUAL(10,res.back().getDia());
	ASSERT_EQUAL(3,res.back().getMes());

	res = cli.veConsultasDisponiveis(1,12,3,"Maria Dinis");
	ASSERT_EQUAL(0,res.size());

	res = cli.veConsultasDisponiveis(1,12,3,"Carolina Silva");
	ASSERT_EQUAL(0,res.size());

	res = cli.veConsultasDisponiveis(12,14,3,"Jaime Luis");
	ASSERT_EQUAL(0,res.size());

}


void test_a3_marcaConsulta() {

	Clinica cli;

	Consulta c1(2,10,3);
	Consulta c2(3,2,3);
	Consulta c3(4,10,3);
	Consulta c4(3,5,3);

	ConsultasVet vet1("Raul Santos");
	vet1.addConsulta(c1);
	vet1.addConsulta(c2);
	vet1.addConsulta(c3);
	vet1.addConsulta(c4);

	cli.addConsultasDisponiveisVet(vet1);

	int horaC=3, diaC=2, mesC=3;
	bool res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Raul Santos");
	ASSERT_EQUAL(true,res);
	ASSERT_EQUAL(2,diaC);
	BST<Consulta> consultasX=cli.getConsultasDisponiveis().front().minhasConsultas;
	Consulta consX=consultasX.findMin();
	consultasX.remove(consX);
	consX=consultasX.findMin();
	consultasX.remove(consX);
	consX=consultasX.findMin();
	consultasX.remove(consX);
	ASSERT_EQUAL(true,consultasX.isEmpty());

	horaC=4, diaC=5, mesC=3;
	res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Raul Santos");
	ASSERT_EQUAL(true,res);
	ASSERT_EQUAL(2,horaC);
	ASSERT_EQUAL(10,diaC);
	consultasX=cli.getConsultasDisponiveis().front().minhasConsultas;
	consX=consultasX.findMin();
	consultasX.remove(consX);
	consX=consultasX.findMin();
	consultasX.remove(consX);
	ASSERT_EQUAL(true,consultasX.isEmpty());

	horaC=4, diaC=15, mesC=3;
	res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Raul Santos");
	ASSERT_EQUAL(false,res);
	consultasX=cli.getConsultasDisponiveis().front().minhasConsultas;
	consX=consultasX.findMin();
	consultasX.remove(consX);
	consX=consultasX.findMin();
	consultasX.remove(consX);
	ASSERT_EQUAL(true,consultasX.isEmpty());

	ConsultasVet vet2("Maria Dinis");
	cli.addConsultasDisponiveisVet(vet2);

	res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Maria Dinis");
	ASSERT_EQUAL(false,res);

	res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Joana Lima");
	ASSERT_EQUAL(false,res);

}


void test_b1_fimConsulta() {

	Clinica cli;
	Animal a1=cli.fimConsulta("bobby","cao");
	ASSERT_EQUAL("bobby", a1.getNome());
	ASSERT_EQUAL(1, a1.getNumConsultas());

	a1=cli.fimConsulta("tareco","gato");
	ASSERT_EQUAL("tareco", a1.getNome());
	ASSERT_EQUAL(1, a1.getNumConsultas());

	a1=cli.fimConsulta("bobby","cao");
	a1=cli.fimConsulta("bobby","cao");
	ASSERT_EQUAL("bobby", a1.getNome());
	ASSERT_EQUAL(3, a1.getNumConsultas());

	a1=cli.fimConsulta("dori","peixe");
	ASSERT_EQUAL("dori", a1.getNome());
	ASSERT_EQUAL(1, a1.getNumConsultas());

	ASSERT_EQUAL(3,cli.getAnimais().size());

}

void test_b2_numEspecie() {

	Clinica cli;

	Animal a1("bobby", "cao");
	Animal a2("dori", "peixe");
	Animal a3("kurika","cao");
	Animal a4("nero","cao");
	Animal a5("nemo","peixe");
	cli.addAnimal(a1);
	cli.addAnimal(a2);
	cli.addAnimal(a3);
	cli.addAnimal(a4);
	cli.addAnimal(a5);
	ASSERT_EQUAL(3,cli.numAnimaisEspecie("cao"));

}

void test_c1_alocaVeterinario() {

	Clinica cli;

	Veterinario vet1("Joao Santos");
	vet1.addAnimal("bobby");
	vet1.addAnimal("tareco");
	vet1.addAnimal("dori");
	cli.addVeterinario(vet1);

	Veterinario vet2("Jaime Dinis");
	cli.addVeterinario(vet2);

	Veterinario vet3("Maria Silva");
	vet3.addAnimal("tareco");
	vet3.addAnimal("lassie");
	cli.addVeterinario(vet3);

	Veterinario vetX=cli.alocaVeterinario("romi");
	ASSERT_EQUAL("Jaime Dinis", vetX.getNome());
	ASSERT_EQUAL(1,vetX.getAnimais().size());
	ASSERT_EQUAL(3,cli.getVeterinarios().size());

	vetX=cli.alocaVeterinario("bravo");
	ASSERT_EQUAL("Jaime Dinis", vetX.getNome());

	vetX=cli.alocaVeterinario("baba");
	ASSERT_EQUAL("Jaime Dinis", vetX.getNome());

	vetX=cli.alocaVeterinario("kurika");
	ASSERT_EQUAL("Maria Silva", vetX.getNome());
	ASSERT_EQUAL(3,vetX.getAnimais().size());
	ASSERT_EQUAL(3,cli.getVeterinarios().size());

}

void test_c2_veterinariosMaisN() {

	Clinica cli;

	Veterinario vet1("Joao Santos");
	vet1.addAnimal("bobby");
	vet1.addAnimal("tareco");
	vet1.addAnimal("dori");
	cli.addVeterinario(vet1);

	Veterinario vet2("Jaime Dinis");
	cli.addVeterinario(vet2);

	Veterinario vet3("Maria Silva");
	vet3.addAnimal("tareco");
	vet3.addAnimal("lassie");
	cli.addVeterinario(vet3);

	Veterinario vet4("Carlos Pereira");
	vet4.addAnimal("bobby");
	vet4.addAnimal("tareco");
	vet4.addAnimal("dori");
	vet4.addAnimal("lassie");
	cli.addVeterinario(vet4);

	list<string> res=cli.veterinariosMaisN(1);
	ASSERT_EQUAL(3,res.size());
	ASSERT_EQUAL("Carlos Pereira",res.front());
	res.pop_front();
	ASSERT_EQUAL("Joao Santos",res.front());

	res=cli.veterinariosMaisN(6);
	ASSERT_EQUAL(0,res.size());

}

void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(test_a1_addConsultas));
	s.push_back(CUTE(test_a2_veConsultasDisponiveis));
	s.push_back(CUTE(test_a3_marcaConsulta));
	s.push_back(CUTE(test_b1_fimConsulta));
	s.push_back(CUTE(test_b2_numEspecie));
	s.push_back(CUTE(test_c1_alocaVeterinario));
	s.push_back(CUTE(test_c2_veterinariosMaisN));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
    return 0;
}



