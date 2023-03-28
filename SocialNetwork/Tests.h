#pragma once

class Teste{
private:
	void initializeaza();
	void testRepos();
	void testAdaugaPrietenie();
	void testStergePrietenie();
	void testTrimiteMesaj();
	void testStergeUtilizator();
	void testAdaugaUtilizator();
	void testStergeMesaj();
	void testPrieteniiUtilizator();
	void testGetConversatie();
public:
	Teste() = default;
	void runTeste();
};