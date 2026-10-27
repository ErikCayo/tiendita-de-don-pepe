//GUARDEN PRIMERO EL CODIGO LUEGO USEN LA OPCION DE AÑADIR PRODUCTO PARA QUE CREE EL TXT Y YA QUEDA
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <fstream> 
#include <sstream> 
#include <conio.h> 
#include <windows.h> 
#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define TECLA_ENTER 13	

	using namespace std;

// funcion para pintar las letras de la consola (ej: 11 es celeste, 14 es amarillo, 7 es blanco)
void cambiarColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

// pausa el programa por los milisegundos que le mande (es para darle tiempo a la animacion)
void pausar(int milisegundos) {
	clock_t tiempo_final = clock() + milisegundos * CLOCKS_PER_SEC / 1000;
	while (clock() < tiempo_final) {}
}

// da el aspecto de animacion con los puntitos
void animarcarga(string mensaje) {
	cout << " " << mensaje;
	for (int i = 0; i < 3; i++) {
		pausar(600);
		cout << ". " << flush;
	}
	cout << "\n" << endl;
}

//clase de los productos, pide para todos los productos el codigo, nombre, marca, precio y stock
class producto {
protected: 
	string codigo;
	string nombre;
	string marca;
	double precio;
	int stock;
	
public:
	producto(string _codigo="", string _nombre="", string _marca="", double _precio=0.0, int _stock=0) {// pone los valores iniciales cuando creemos un producto, se sustituiran al pedirnos esos datos
		codigo = _codigo;
		nombre = _nombre;
		marca = _marca;
		precio = _precio;
		stock = _stock;// lo primero que pedira el codigo al ingresar un nuevo producto
	}
	
	// getter para sacar la info privada desde afuera de la clase
	string getcodigo() { return codigo; }
	string getnombre() { return nombre; }
	string getmarca() { return marca; }
	double getprecio() { return precio; }
	int getstock() { return stock; }
	
	// setter para cuando añadamos mas producto restemos cuando vendamos
	void setstock(int nuevo_stock) { stock = nuevo_stock; }
	void reducircantidad(int cantidad) { stock -= cantidad; }
	
	// virtuales para que podamos usar el polimorfismo, osea pedir caracteristicas aparte a cada producto
	virtual int gettiponumerico() { return 0; }
	virtual string getspecliena() { return ""; }
	
	// mostrara los datos basicos, los generales que del padre
	virtual void mostrarespecificaciones() {
		cout << "[" << codigo << "] " << nombre << " (" << marca 
			<< ") - precio: $" << precio << " - stock: " << stock << endl;
	}
	
	virtual ~producto() {}
};

//hijos

// 1. Computadora
class computadora : public producto {
private:
	string procesador; int ram; int espacio; string grafica; string monitor; string audio; string rgb;
public:
	computadora(string _cod, string _nom, string _mar, double _pre, int _st, string _proc, int _ram, int _esp, string _graf, string _mon, string _aud, string _rgb)
		: producto(_cod, _nom, _mar, _pre, _st) {
		procesador = _proc; ram = _ram; espacio = _esp; grafica = _graf; monitor = _mon; audio = _aud; rgb = _rgb;
	}
	int gettiponumerico() override { return 1; } 
	string getspecliena() override {
		return procesador + "," + to_string(ram) + "," + to_string(espacio) + "," + grafica + "," + monitor + "," + audio + "," + rgb;
	}
	void mostrarespecificaciones() override {
		producto::mostrarespecificaciones(); 
		cout << " -> specs: computadora | cpu: " << procesador << " | ram: " << ram << "gb | disco: " << espacio 
			<< "gb | grafica: " << grafica << " | monitor: " << monitor << " | rgb: " << rgb << endl;
	}
};

// 2. Celular
class celular : public producto {
private:
	string procesador; int ram; int espacio; int bateria; string audio; string camara;
public:
	celular(string _cod, string _nom, string _mar, double _pre, int _st, string _proc, int _ram, int _esp, int _bat, string _aud, string _cam)
		: producto(_cod, _nom, _mar, _pre, _st) {
		procesador = _proc; ram = _ram; espacio = _esp; bateria = _bat; audio = _aud; camara = _cam;
	}
	int gettiponumerico() override { return 2; }
	string getspecliena() override {
		return procesador + "," + to_string(ram) + "," + to_string(espacio) + "," + to_string(bateria) + "," + audio + "," + camara;
	}
	void mostrarespecificaciones() override {
		producto::mostrarespecificaciones();
		cout << " -> specs: celular | cpu: " << procesador << " | ram: " << ram << "gb | disco: " << espacio 
			<< "gb | bateria: " << bateria << "mah | camara: " << camara << endl;
	}
};

// 3. Laptop
class laptop : public producto {
private:
	string procesador; int ram; int espacio; string grafica; string monitor; string audio; string rgb; int bateria;
public:
	laptop(string _cod, string _nom, string _mar, double _pre, int _st, string _proc, int _ram, int _esp, string _graf, string _mon, string _aud, string _rgb, int _bat)
		: producto(_cod, _nom, _mar, _pre, _st) {
		procesador = _proc; ram = _ram; espacio = _esp; grafica = _graf; monitor = _mon; audio = _aud; rgb = _rgb; bateria = _bat;
	}
	int gettiponumerico() override { return 3; }
	string getspecliena() override {
		return procesador + "," + to_string(ram) + "," + to_string(espacio) + "," + grafica + "," + monitor + "," + audio + "," + rgb + "," + to_string(bateria);
	}
	void mostrarespecificaciones() override {
		producto::mostrarespecificaciones();
		cout << " -> specs: laptop | cpu: " << procesador << " | ram: " << ram << "gb | disco: " << espacio 
			<< "gb | pantalla: " << monitor << " | bateria: " << bateria << "wh" << endl;
	}
};

// 4. Auriculares
class auriculares : public producto {
private:
	string tipo; string conexion; string microfono; string bateria;
public:
	auriculares(string _cod, string _nom, string _mar, double _pre, int _st, string _tipo, string _con, string _mic, string _bat)
		: producto(_cod, _nom, _mar, _pre, _st) {
		tipo = _tipo; conexion = _con; microfono = _mic; bateria = _bat;
	}
	int gettiponumerico() override { return 4; }
	string getspecliena() override { return tipo + "," + conexion + "," + microfono + "," + bateria; }
	void mostrarespecificaciones() override {
		producto::mostrarespecificaciones();
		cout << " -> specs: auriculares | tipo: " << tipo << " | conexion: " << conexion << " | mic: " << microfono << " | bateria: " << bateria << endl;
	}
};

// 5. Parlantes
class parlantes : public producto {
private:
	int potencia; string conexion; int bateria; string tipo;
public:
	parlantes(string _cod, string _nom, string _mar, double _pre, int _st, int _pot, string _con, int _bat, string _tipo)
		: producto(_cod, _nom, _mar, _pre, _st) {
		potencia = _pot; conexion = _con; bateria = _bat; tipo = _tipo;
	}
	int gettiponumerico() override { return 5; }
	string getspecliena() override { return to_string(potencia) + "," + conexion + "," + to_string(bateria) + "," + tipo; }
	void mostrarespecificaciones() override {
		producto::mostrarespecificaciones();
		cout << " -> specs: parlantes | potencia: " << potencia << "w | conexion: " << conexion << " | bateria: " << bateria << "mah" << endl;
	}
};

// 6. Accesorios
class accesorios : public producto {
private:
	string tipo; string compatibilidad; string descripcion;
public:
	accesorios(string _cod, string _nom, string _mar, double _pre, int _st, string _tipo, string _comp, string _desc)
		: producto(_cod, _nom, _mar, _pre, _st) {
		tipo = _tipo; compatibilidad = _comp; descripcion = _desc;
	}
	int gettiponumerico() override { return 6; }
	string getspecliena() override { return tipo + "," + compatibilidad + "," + descripcion; }
	void mostrarespecificaciones() override {
		producto::mostrarespecificaciones();
		cout << " -> specs: accesorio | tipo: " << tipo << " | compatibilidad: " << compatibilidad << " | desc: " << descripcion << endl;
	}
};

//inventario

// guarda, busca y sincroniza con el txt
class inventario {
private:
	string id;
	vector<producto*> listaproductos;
	
public:
	inventario(string _id="") { id = _id; }
	
	void agregarproducto(producto* p) {//mete el nuevo producto y guarda
		listaproductos.push_back(p);
		actualizararchivotxt(); 
	}
	
	producto* buscarporcodigo(string cod) {//busca segun el codigo del producto
		for (size_t i = 0; i < listaproductos.size(); i++) {
			if (listaproductos[i]->getcodigo() == cod) return listaproductos[i];
		}
		return nullptr; 
	}
	
	// reescribe el txt con los datos del nuevo producto
	void actualizararchivotxt() {
		ofstream archivo("inventario.txt");
		if (archivo.is_open()) {
			for (size_t i = 0; i < listaproductos.size(); i++) {
				archivo << listaproductos[i]->gettiponumerico() << ","
					<< listaproductos[i]->getcodigo() << "," 
					<< listaproductos[i]->getnombre() << "," 
					<< listaproductos[i]->getmarca() << "," 
					<< listaproductos[i]->getprecio() << "," 
					<< listaproductos[i]->getstock();
				if (listaproductos[i]->gettiponumerico() != 0) {
					archivo << "," << listaproductos[i]->getspecliena();
				}
				archivo << "\n";
			}
			archivo.close();
		}
	}
	
	//lee el txt y vota los datos del procducto
	void cargarproductosdesdearchivo() {
		ifstream archivo("inventario.txt");
		if (!archivo.is_open()) return;
		string linea;
		while (getline(archivo, linea)) {
			if(linea.empty()) continue;
			stringstream ss(linea);
			string dato1, cod, nom, mar, pre_str, st_str;
			getline(ss, dato1, ',');
			if (dato1 != "1" && dato1 != "2" && dato1 != "3" && dato1 != "4" && dato1 != "5" && dato1 != "6") {
				cod = dato1; 
				getline(ss, nom, ','); getline(ss, mar, ','); getline(ss, pre_str, ','); getline(ss, st_str, ',');
				double pre = stod(pre_str); int st = stoi(st_str);
				listaproductos.push_back(new producto(cod, nom, mar, pre, st));
			}
			else {
				int tipo = stoi(dato1);
				getline(ss, cod, ','); getline(ss, nom, ','); getline(ss, mar, ','); getline(ss, pre_str, ','); getline(ss, st_str, ',');
				double pre = stod(pre_str); int st = stoi(st_str);
				string s1, s2, s3, s4, s5, s6, s7;
				if (tipo == 1) { 
					getline(ss, s1, ','); getline(ss, s2, ','); getline(ss, s3, ','); getline(ss, s4, ','); getline(ss, s5, ','); getline(ss, s6, ','); getline(ss, s7, ',');
					listaproductos.push_back(new computadora(cod, nom, mar, pre, st, s1, stoi(s2), stoi(s3), s4, s5, s6, s7));
				}
				else if (tipo == 2) { 
					getline(ss, s1, ','); getline(ss, s2, ','); getline(ss, s3, ','); getline(ss, s4, ','); getline(ss, s5, ','); getline(ss, s6, ',');
					listaproductos.push_back(new celular(cod, nom, mar, pre, st, s1, stoi(s2), stoi(s3), stoi(s4), s5, s6));
				}
				else if (tipo == 3) { 
					getline(ss, s1, ','); getline(ss, s2, ','); getline(ss, s3, ','); getline(ss, s4, ','); getline(ss, s5, ','); getline(ss, s6, ','); getline(ss, s7, ','); getline(ss, s2, ',');
					listaproductos.push_back(new laptop(cod, nom, mar, pre, st, s1, stoi(s2), stoi(s3), s4, s5, s6, s7, stoi(s2)));
				}
				else if (tipo == 4) { 
					getline(ss, s1, ','); getline(ss, s2, ','); getline(ss, s3, ','); getline(ss, s4, ',');
					listaproductos.push_back(new auriculares(cod, nom, mar, pre, st, s1, s2, s3, s4));
				}
				else if (tipo == 5) { 
					getline(ss, s1, ','); getline(ss, s2, ','); getline(ss, s3, ','); getline(ss, s4, ',');
					listaproductos.push_back(new parlantes(cod, nom, mar, pre, st, stoi(s1), s2, stoi(s3), s4));
				}
				else if (tipo == 6) { 
					getline(ss, s1, ','); getline(ss, s2, ','); getline(ss, s3, ',');
					listaproductos.push_back(new accesorios(cod, nom, mar, pre, st, s1, s2, s3));
				}
			}
		}
		archivo.close();
		animarcarga("si esto se ve entonces logro leer el txt");
	}
	
	// da la lista de productos y si no hay suelta el mensaje
	void mostrarproductos() {
		cout << "\n=========================================" << endl;
		cout << "                 inventario               " << endl;
		cout << "=========================================" << endl;
		if (listaproductos.empty()) {
			cout << "el inventario ta vacio" << endl;
			return;
		}
		for (size_t i = 0; i < listaproductos.size(); i++) {
			listaproductos[i]->mostrarespecificaciones();
			cout << "-----------------------------------------" << endl;
		}
	}
	
	// libera la memoria
	~inventario() {
		for (size_t i = 0; i < listaproductos.size(); i++) delete listaproductos[i];
		listaproductos.clear();
	}
};

// venta
class venta {
private:
	string idventa;
	double total;
	producto* productoscomprados[50];
	int cantidades[50];
	int cantidad_items;
public:
	venta(string _id) {
		idventa = _id;
		total = 0.0;
		cantidad_items = 0;
	}
	
	void registrarlineadeventa(producto* p, int cant) {// suma el valor del pruducto y lo resta del stock
		if (cantidad_items < 50) {
			productoscomprados[cantidad_items] = p; 
			cantidades[cantidad_items] = cant;      
			p->reducircantidad(cant);               
			total += (p->getprecio() * cant); 
			cantidad_items++;                       
		}
	}
	
	double calculartotal() { return total; }
	
	void imprimirrecibo() {//menu de venta
		animarcarga("animacion de cobro");
		cout << "\n=========================================" << endl;
		cout << "                  boleta                 " << endl;
		cout << "=========================================" << endl;
		for (int i = 0; i < cantidad_items; i++) {
			cout << " * " << productoscomprados[i]->getnombre() << " x" << cantidades[i] << " | subtotal: S/" << (productoscomprados[i]->getprecio() * cantidades[i]) << endl;
		}
		cout << "=========================================" << endl;
		cout << " precio total: S/" << total << endl;
		cout << "=========================================" << endl;
	}
};

// personal

class persona {
protected: string dni; string nombre;
public:
	persona(string _dni="", string _nombre="") { dni = _dni; nombre = _nombre; }
	virtual void mostrardatos() { cout << "dni: " << dni << " | nombre: " << nombre; }
	virtual ~persona() {}
};

class administrador : public persona {
private: string codigo;
public:
	administrador(string d, string n, string c) : persona(d, n) { codigo = c; }
	void mostrardatos() override { persona::mostrardatos(); cout << " | puesto: administrador | cod: " << codigo << endl; }
};

class limpieza : public persona {
private: string zona;
public:
	limpieza(string d, string n, string z) : persona(d, n) { zona = z; }
	void mostrardatos() override { persona::mostrardatos(); cout << " | puesto: personal limpieza | zona: " << zona << endl; }
};

class cajero : public persona {
private: string caja;
public:
	cajero(string d, string n, string c) : persona(d, n) { caja = c; }
	void mostrardatos() override { persona::mostrardatos(); cout << " | puesto: cajero | terminal: " << caja << endl; }
};

class distribuidor : public persona {
private: string vehiculo;
public:
	distribuidor(string d, string n, string v) : persona(d, n) { vehiculo = v; }
	void mostrardatos() override { persona::mostrardatos(); cout << " | puesto: distribuidor | ruta: " << vehiculo << endl; }
};

class orientador : public persona {
private: string modulo;
public:
	orientador(string d, string n, string m) : persona(d, n) { modulo = m; }
	void mostrardatos() override { persona::mostrardatos(); cout << " | puesto: orientador tecnico | modulo: " << modulo << endl; }
};

//menu interactivo

void mostrarMenuInteractivo(int opcionSeleccionada) {
	system("cls"); // limpia la pantalla 
	
	cambiarColor(11);
	cout << "=========================================" << endl;
	cout << "          tiendita de don pepe           " << endl;
	cout << "=========================================" << endl;
	
	string opciones[6] = {
		"ver todos los productos",
			"registrar un producto nuevo",
			"procesar una venta",
			"ver personal de la tienda",
			"añadir stock a un producto",
			"salir del sistema"
	};
	
	for(int i = 0; i < 6; i++) {
		if(i == opcionSeleccionada) {
			cambiarColor(14);
			cout << " ==> [ " << (i + 1) << ". " << opciones[i] << " ]" << endl;
		} else {
			cambiarColor(7);
			cout << "     " << (i + 1) << ". " << opciones[i] << "" << endl;
		}
	}
	
	cambiarColor(3);
	cout << "=========================================" << endl;
	cout << " [muevete con las flechitas de arriba y abajo, y presiona con enter]" << endl;
	cambiarColor(7);
}

int main() {
	inventario miinventario("inv-donpepe");// carga el txt
	miinventario.cargarproductosdesdearchivo();
	
	administrador admin1("60524103", "Erik Cayo", "admin");// declaro chambeadores
	limpieza limpieza1("dni generico", "mohamad quispe", "general");
	cajero cajero1("dni generico", "Halin Chura", "caja 1");
	distribuidor dist1("dni generico", "Renato Butillier", "directa desde el punto de origen (6:30 AM) hasta la tienda (9:00 AM)");
	orientador orient1("61205394", "Jeffri Coila", "atencion al cliente");
	
	int seleccion = 0; //guarda en que opcion del menu estamos
	char tecla;
	int contador_ventas = 1;
	
	// redibuja el menu cuando salgamos de donde estabamos
	do {
		mostrarMenuInteractivo(seleccion);
		
		tecla = _getch();
		
		if(tecla == 0 || tecla == -32) {
			tecla = _getch(); 
			if(tecla == TECLA_ARRIBA) {
				seleccion--;
				if(seleccion < 0) seleccion = 5; //si sube de mas que lo mande pa abajo en un efecto asi como que arriba es abajo
			}
			else if(tecla == TECLA_ABAJO) {
				seleccion++;
				if(seleccion > 5) seleccion = 0;
			}
		}
		else if(tecla == TECLA_ENTER) {// si presiono enter toma la opcion
			system("cls"); 
			cambiarColor(7); 
			
			// opcion 1
			if (seleccion == 0) {
				miinventario.mostrarproductos(); 
			}
			
			// opcion 2
			else if (seleccion == 1) {
				int tipo_prod = 0;
				cout << "\n--- tipos de producto ---" << endl;
				cout << " 1. computadora | 2. celular   | 3. laptop" << endl;
				cout << " 4. auriculares | 5. parlantes | 6. accesorio" << endl;
				cout << " elija el tipo (1-6): "; cin >> tipo_prod;
				string cod, nom, mar; double pre; int st = 0; 
				cout << "\n--- datos generales ---" << endl;
				cout << " ingrese codigo: "; cin >> cod; cin.ignore(); 
				cout << " ingrese nombre: "; getline(cin, nom);
				cout << " ingrese marca: "; getline(cin, mar);
				cout << " ingrese precio: S/"; cin >> pre;
				if (tipo_prod == 1) {
					string proc, graf, aud, rgb, mon; int ram, esp;
					cout << " procesador: "; cin >> proc; cout << " ram (gb): "; cin >> ram;
					cout << " espacio disco (gb): "; cin >> esp; cout << " tarjeta grafica: "; cin >> graf;
					cout << " monitor specs: "; cin >> mon; cout << " audio specs: "; cin >> aud;
					cout << " iluminacion rgb (si/no): "; cin >> rgb;
					miinventario.agregarproducto(new computadora(cod, nom, mar, pre, st, proc, ram, esp, graf, mon, aud, rgb));
				}
				else if (tipo_prod == 2) {
					string proc, aud, cam; int ram, esp, bat;
					cout << " procesador: "; cin >> proc; cout << " ram (gb): "; cin >> ram;
					cout << " espacio (gb): "; cin >> esp; cout << " bateria (mah): "; cin >> bat;
					cout << " sistema audio: "; cin >> aud; cout << " camara (mp): "; cin >> cam;
					miinventario.agregarproducto(new celular(cod, nom, mar, pre, st, proc, ram, esp, bat, aud, cam));
				}
				else if (tipo_prod == 3) {
					string proc, graf, mon, aud, rgb; int ram, esp, bat;
					cout << " procesador: "; cin >> proc; cout << " ram (gb): "; cin >> ram;
					cout << " espacio (gb): "; cin >> esp; cout << " grafica: "; cin >> graf;
					cout << " pantalla: "; cin >> mon; cout << " audio: "; cin >> aud;
					cout << " rgb: "; cin >> rgb; cout << " bateria (wh): "; cin >> bat;
					miinventario.agregarproducto(new laptop(cod, nom, mar, pre, st, proc, ram, esp, graf, mon, aud, rgb, bat));
				}
				else if (tipo_prod == 4) {
					string tipo, con, mic, bat;
					cout << " tipo (diadema/in-ear): "; cin >> tipo; cout << " conexion: "; cin >> con;
					cout << " microfono (si/no): "; cin >> mic; cout << " duracion bateria: "; cin >> bat;
					miinventario.agregarproducto(new auriculares(cod, nom, mar, pre, st, tipo, con, mic, bat));
				}
				else if (tipo_prod == 5) {
					int pot, bat; string con, tipo;
					cout << " potencia (w): "; cin >> pot; cout << " conexion: "; cin >> con;
					cout << " bateria (mah): "; cin >> bat; cout << " tipo (portatil/mesa): "; cin >> tipo;
					miinventario.agregarproducto(new parlantes(cod, nom, mar, pre, st, pot, con, bat, tipo));
				}
				else if (tipo_prod == 6) {
					string tipo, comp, desc;
					cout << " tipo de accesorio: "; cin >> tipo; cout << " compatibilidad: "; cin >> comp;
					cin.ignore(); cout << " descripcion breve: "; getline(cin, desc);
					miinventario.agregarproducto(new accesorios(cod, nom, mar, pre, st, tipo, comp, desc));
				}
				cout << "\n -> producto registrado" << endl;
			}
			
			// opcion 3
			else if (seleccion == 2) {
				string id_v = "v-" + to_string(contador_ventas); venta nueva_venta(id_v);
				string cod_buscar; int cant_vender; char continuar = 's';
				cout << "\n--- modulo de punto de venta ---" << endl;
				while (continuar == 's' || continuar == 'S') {
					cout << " ingrese el codigo del producto que vendes: "; cin >> cod_buscar;
					producto* prod_encontrado = miinventario.buscarporcodigo(cod_buscar);
					if (prod_encontrado != nullptr) {
						cout << " producto: " << prod_encontrado->getnombre() << " | stock actual: " << prod_encontrado->getstock() << endl;
						cout << " ingrese cantidad: "; cin >> cant_vender;
						if (cant_vender <= prod_encontrado->getstock() && cant_vender > 0) {
							nueva_venta.registrarlineadeventa(prod_encontrado, cant_vender);
							cout << " -> añadido al sistema" << endl;
						} else {
							cout << " -> no tenemos suficiente de ese producto " << endl;
						}
					} else {
						cout << " -> no tenemos ese producto" << endl;
					}
					cout << " ¿desea agregar otro articulo a la boleta? (s/n): "; cin >> continuar;
				}
				if (nueva_venta.calculartotal() > 0) {
					nueva_venta.imprimirrecibo();
					miinventario.actualizararchivotxt();
					contador_ventas++;
				}
			}
			
			// opcion 4
			else if (seleccion == 3) {
				cout << "\n-------  personal  -------" << endl;
				cout << "-----------------------------------------" << endl;
				admin1.mostrardatos(); limpieza1.mostrardatos(); cajero1.mostrardatos(); dist1.mostrardatos(); orient1.mostrardatos();
				cout << "-----------------------------------------" << endl;
			}
			
			// opcion 5
			else if (seleccion == 4) { 
				string cod_abastecer; int cant_ingreso;
				cout << "\n--- ingresar cantidad de producto ---" << endl;
				cout << " ingrese el codigo del producto para añadir stock "; cin >> cod_abastecer;
				producto* prod = miinventario.buscarporcodigo(cod_abastecer);
				if (prod != nullptr) {
					cout << " producto: " << prod->getnombre() << " | stock actual: " << prod->getstock() << endl;
					cout << " ingrese la cantidad del producto a ingresar: "; cin >> cant_ingreso;
					if (cant_ingreso > 0) {
						prod->setstock(prod->getstock() + cant_ingreso);
						miinventario.actualizararchivotxt(); 
						animarcarga("animacion de que estamos añadiendo stock");
						cout << "nuevo stock: " << prod->getstock() << " unidades" << endl;
					} else {
						cout << "cantidad no valida" << endl;
					}
				} else {
					cout << "producto no encontrado" << endl;
				}
			}
			
			// opcion 6
			else if (seleccion == 5) {
				cambiarColor(10);
				animarcarga("cerrando la tiendita");
				cambiarColor(7);
			}
			
			// pausa para que de tiempo a leer
			if (seleccion != 5) {
				cout << "\nPresione cualquier tecla para volver al menu...";
				_getch();
			}
		}
		
	} while (seleccion != 5 || tecla != TECLA_ENTER);
	
	return 0;
}
