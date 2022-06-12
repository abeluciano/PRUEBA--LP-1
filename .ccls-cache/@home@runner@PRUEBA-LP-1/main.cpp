#include <iostream>
#include <fstream>

using namespace std;

string Cocinas[5][6], Indice_de_Cocina[6];

int Numero_de_Boleto = 0, Cantidad_de_Ventas[5], Cantidad_de_Unidades_Vendidas[5];

float Importe_Total_Vendido[5], Configuracion_de_Tienda[4];

/*===========GUARDAR_DATOS============*/

void Guardar_Lista_de_Cocinas() {
  string s1[5], s2[5];
  ifstream Lista_de_Cocinas;
  
  Lista_de_Cocinas.open("cocina-data.txt");
  
  if (Lista_de_Cocinas.is_open()) {
    for (int i = 0; i < 5; i++) {
      Lista_de_Cocinas >> s1[i] >> s2[i];
      for (int j = 0; j < 5; j++) {
      Lista_de_Cocinas >> Cocinas[i][j+1];
      }
    }
    
    for (int i = 0; i < 5; i++) {
      Cocinas[i][0] = s1[i] + " " + s2[i];
    }  
    
    Lista_de_Cocinas.close();
  }
  else {
    cout << "No se encontro el archivo, revise" << endl;
  }
}

void Guardar_Configuracion() {
  ifstream Configuracion;
  Configuracion.open("config-tienda.txt");
  
  if (Configuracion.is_open()) {
    for (int i = 0; i < 4; i++) {
      Configuracion >> Configuracion_de_Tienda[i];
    }
    Configuracion.close();
  }
}

void Describir_Cocina(int NumCocina) {
  for (int j = 1; j < 6; j++) {
    cout << Indice_de_Cocina[j] << Cocinas[NumCocina][j] << endl;
  }
}
/*==========ERROR_DEL_CIN(BUCLE)==========*/
void Error_cin() {
  if (! cin) {                              
    cin.clear();                          
    cin.ignore(10000,'\n');; // para evitar bucles 
  }
}
/*==========MENSAJE_DE_ERROR==========*/

void Mostrar_Mensaje_de_Error() {
  cout << "\nError, la opción elegida no exite. Vuelve a intentarlo...\n\n";
}
/* ==========CONFIGURACIÓN========== */

void Configurar_Cantidad_Optima() {
  cout << "Cantidad optima actual: " << Configuracion_de_Tienda[3] << endl;
  
  if (Configuracion_de_Tienda[3] > 0) {
    cout << "Indique la nueva cantidad optima: ";
    cin >> Configuracion_de_Tienda[3];
  }
  else {
    Mostrar_Mensaje_de_Error();
    return Configurar_Cantidad_Optima();
  }
}

void Configurar_Descuento() {
  int Opc_Dsc = 0;
  
  for (int i = 0; i < 3; i++) {
    cout << i+1 << "= Descuento " << i + 1 << " : " << Configuracion_de_Tienda[i] << endl;
  }
  
  cout << "\nIndique el Descuento a modificar: ";
  cin >> Opc_Dsc;
  Error_cin();
  if (Opc_Dsc > 0 && Opc_Dsc < 4) {
    cout << "\nIndique el nuevo Descuento: ";
    cin >> Configuracion_de_Tienda[Opc_Dsc-1];
  }
  else {
    Mostrar_Mensaje_de_Error();
    return Configurar_Descuento();
  }
}

void Mostrar_Configuracion() {
  int Opc_Configuracion;
  cout << "1=Cofigurar_Descuentos\n2=Cofigurar_cantidad_optima\n";
  cout << "Elija la opción: ";
  cin >> Opc_Configuracion;
  Error_cin();
  switch (Opc_Configuracion) {
    case 1: Configurar_Descuento();
      break;
    case 2: Configurar_Cantidad_Optima();
      break;
    default: Mostrar_Mensaje_de_Error(); 
      return Mostrar_Configuracion();
      break;
  }
}
/*============REPORTES==============*/

void Mostrar_Ventas_en_Relacion_a_la_Venta_Optima() {

  cout << "VENTAS EN RELACIÓN A LA VENTA ÓPTIMA\n\n";

  for (int i = 0; i < 5; i++) {
    cout << "Modelo             :  " << Cocinas[i][0] << endl;
    cout << "Unidades vendidas  :  " << Cantidad_de_Unidades_Vendidas[i] << " (";
    
    if (Configuracion_de_Tienda[3] > Cantidad_de_Unidades_Vendidas[i]) {
      cout << (Cantidad_de_Unidades_Vendidas[i] - Configuracion_de_Tienda[3]) * (-1) << " menos";
    }
    else if (Configuracion_de_Tienda[3] < Cantidad_de_Unidades_Vendidas[i]) {
      cout << Cantidad_de_Unidades_Vendidas[i] - Configuracion_de_Tienda[3] << " más";
    }
    else if (Configuracion_de_Tienda[3] == Cantidad_de_Unidades_Vendidas[i]) {
      cout << "igual";
    } 
    cout << " que la cantidad óptima)" << endl << endl;
  }
}

void Mostrar_Ventas_por_Modelo() {
  
  cout << "\tVENTAS POR MODELO" << endl << endl;
  
  for (int i = 0; i < 5; i++) {
    cout << "Modelo                         :  " << Cocinas[i][0] << endl;
    cout << "Cantidad de ventas             :  " << Cantidad_de_Ventas[i] << endl;
    cout << "Cantidad de unidades vendidas  :  " << Cantidad_de_Unidades_Vendidas[i] << endl;
    cout << "Importe total vendido          :  " << Importe_Total_Vendido[i] << endl << endl;
  }
}

void Mostrar_Reportes() {
  int Opc_Reportes;
  cout << "1 = Ventas por modelo\n2 = Ventas en relación a la venta óptima\n";
  cout << "Elija la opción: ";
  cin >> Opc_Reportes;
  Error_cin();
  switch (Opc_Reportes) {
    case 1: Mostrar_Ventas_por_Modelo();
      break;
    case 2: Mostrar_Ventas_en_Relacion_a_la_Venta_Optima();
      break;
    default: Mostrar_Mensaje_de_Error(); 
      return Mostrar_Reportes();
      break;
  }
}

/*============VENDER================*/

void Vender_Cocina(int Indice_de_Cocina) {
  int CantCocinas_a_Comprar = 0;
  float Importe_de_Compra, Importe_Final, Precio, Descuento;
  string NBoleto(to_string(Numero_de_Boleto));
  ofstream Boletas;
  
  cout << "Elija la cantidad de cocinas a comprar: ";
  cin >> CantCocinas_a_Comprar;

  Cantidad_de_Unidades_Vendidas[Indice_de_Cocina] += CantCocinas_a_Comprar;
  
  Precio = stof(Cocinas[Indice_de_Cocina][1]);
  
  Importe_de_Compra = CantCocinas_a_Comprar * Precio;


  if (CantCocinas_a_Comprar >= 1 && CantCocinas_a_Comprar < 6) {
    Descuento = Importe_de_Compra * (Configuracion_de_Tienda[0]/100);
  }
    
  else if (CantCocinas_a_Comprar > 5 && CantCocinas_a_Comprar < 11) {
    Descuento = Importe_de_Compra * (Configuracion_de_Tienda[1]/100);
  }
    
  else if (CantCocinas_a_Comprar > 9) {
    Descuento = Importe_de_Compra * (Configuracion_de_Tienda[2]/100);
  }
    
  else {
    cout << "Revise que la cantidad sea un entero positivo" << endl;
  }
  
  Importe_Final = Importe_de_Compra - Descuento;
  
  Importe_Total_Vendido[Indice_de_Cocina] += Importe_Final;
  
  Boletas.open("boleta_<" + NBoleto + ">.txt");
  
  if (Boletas.is_open()) {
    Boletas << "BOLETA DE VENTA: " << Numero_de_Boleto << endl << endl;
    Boletas << "Modelo         : " << Cocinas[Indice_de_Cocina][0] << endl;
    Boletas << "Precio         : " << "S/ " << Cocinas[Indice_de_Cocina][1] << endl;
    Boletas << "Cantidad       : " << CantCocinas_a_Comprar << endl;
    Boletas << "Importe compra : " << "S/ " << Importe_de_Compra << endl;
    Boletas << "Descuento      : " << "S/ " << Descuento << endl;
    Boletas << "Importe pagar  : " << "S/ " << Importe_Final << endl;     
    Boletas.close();
    Numero_de_Boleto ++;
  }
  else {
    cout << "El archivo no pudo ser cargado, vuelva a intentarlo..." << endl;
    return Vender_Cocina(Indice_de_Cocina); 
  }
}

void Mostrar_Vender_Cocina() {
  int Opc_VCocina;

  cout << "¿Qué modelo desea comprar?\n";
  cout << "1 = Mabe EMP6120PG0\n2 = Indurama Parma\n3 = Sole COSOL027\n4 = Coldex CX602\n5 = Reco Dakota\n";
  cout << "Elija la opcion: ";
  cin >> Opc_VCocina;
  Error_cin();
    switch(Opc_VCocina){
      case 1: cout << "Cocina 1:\n\n";
        Vender_Cocina(Opc_VCocina-1);
        Cantidad_de_Ventas[0]++;
        break;
      case 2: cout << "Cocina 2:\n\n";
        Vender_Cocina(Opc_VCocina-1);
        Cantidad_de_Ventas[1]++;
        break;
      case 3: cout << "Cocina 3:\n\n";
        Vender_Cocina(Opc_VCocina-1);
        Cantidad_de_Ventas[2]++;
        break;
      case 4: cout << "Cocina 4:\n\n";
        Vender_Cocina(Opc_VCocina-1);
        Cantidad_de_Ventas[3]++;
        break;
      case 5: cout << "Cocina 5:\n\n";
        Vender_Cocina(Opc_VCocina-1);
        Cantidad_de_Ventas[4]++;
        break;
      default: Mostrar_Mensaje_de_Error();
        return Mostrar_Vender_Cocina();
        break;
    } 
}


/*============MANTENIMIENTO==========*/

void Modificar_Cocina(int Indice_Cocina) {
  int Opc_ModificarC;
  cout << "\n ¿Desea modificar por partes o todo?" << endl;
  cout << "\n 1.- Por partes ";
  cout << "\n 2.- Todo ";
  cout << "\n 3.- N/A\n";
  cin >> Opc_ModificarC;
  if(Opc_ModificarC == 1){
    int Opc_PorPartes;
    
    cout << "\n 1.- Por partes " << endl;
    cout << "Elija que deseea moficar:\n1 = PRECIO\n2 = ALTO\n3 = ANCHO\n4 = FONDO\n5 = QUEMDORES\n";
    cin >> Opc_PorPartes;
    Error_cin();
    switch (Opc_PorPartes){
      case 1:
        cout << "Indique el nuevo precio\n";
        cin >> Cocinas[Indice_Cocina][1];
        break;
      case 2:
        cout << "Indique el alto\n";
        cin >> Cocinas[Indice_Cocina][2];
        break;
      case 3:
        cout << "Indique el nuevo ancho\n";
        cin >> Cocinas[Indice_Cocina][3];
        break;
      case 4:
        cout << "Indique el nuevo fondo\n";
        cin >> Cocinas[Indice_Cocina][4];
        break;
      case 5:
        cout << "Indique catidad de quemadores\n";
        cin >> Cocinas[Indice_Cocina][5];
        break;
      default: Mostrar_Mensaje_de_Error();
        return Modificar_Cocina(Indice_Cocina);
        break;
    }
  }
  else if(Opc_ModificarC == 2) {
    cout << "\nIndique el nuevo precio\n";
    cin >> Cocinas[Indice_Cocina][1];
    cout << "Indique el alto\n";
    cin >> Cocinas[Indice_Cocina][2];
    cout << "Indique el nuevo fondo\n";
    cin >> Cocinas[Indice_Cocina][3];
    cout << "Indique el nuevo fondo\n";
    cin >> Cocinas[Indice_Cocina][4];
    cout << "Indique catidad de quemadores\n";
    cin >> Cocinas[Indice_Cocina][5];
  }
  else {
    return Modificar_Cocina(Indice_Cocina);
  }
}

void Mostrar_Modificar_Cocina () {
  int Opc_Modificar;
  cout<< "Elija cocina a modificar\n";
  cout << "1 = Mabe EMP6120PG0\n2 = Indurama Parma\n3 = Sole COSOL027\n4 = Coldex CX602\n5 = Reco Dakota\n ";
  cout << "Elija la opcion\n";
  cin >> Opc_Modificar;
  Error_cin();
  switch(Opc_Modificar){
    case 1:
      Modificar_Cocina(0);
      break;
    case 2: 
      Modificar_Cocina(1);
      break;
    case 3: 
      Modificar_Cocina(2);
      break;
    case 4: 
      Modificar_Cocina(3);
      break;
    case 5:  
      Modificar_Cocina(4);
      break;
    default:
      Mostrar_Mensaje_de_Error();
      return Mostrar_Modificar_Cocina ();
        break;
    } 
}

void Mostrar_Lista_de_Cocinas () {
  
  for (int i = 0; i < 5; i++) {
    cout << "\n============================";
    for (int j = 0; j < 6; j++) {
      cout << endl << Indice_de_Cocina[j] << Cocinas[i][j];
      if (j > 1 && j < 5) {
        cout << " cm";
      }
    }
  }
  cout << "\n============================\n";
}

void Consultar_Cocina () {
  int Opc_ConsC;
  
  cout << "1 = Mabe EMP6120PG0\n2 = Indurama Parma\n3 = Sole COSOL027\n4 = Coldex CX602\n5 = Reco Dakota\n";
  cout << "Elija la opcion: ";
  cin >> Opc_ConsC;
  Error_cin();
  switch(Opc_ConsC){
    case 1: cout << "Cocina 1:\n\n";
      Describir_Cocina(0);
      break;
    case 2: cout << "Cocina 2:\n\n";
      Describir_Cocina(1);
      break;
    case 3: cout << "Cocina 3:\n\n";
      Describir_Cocina(2);
      break;
    case 4: cout << "Cocina 4:\n\n";
      Describir_Cocina(3);
      break;
    case 5: cout << "Cocina 5:\n\n";
      Describir_Cocina(4);
      break;
    default: Mostrar_Mensaje_de_Error();
      return Consultar_Cocina ();
      break;
  } 
}

void Mostrar_Mantenimiento () {
  int Opc_Mante;
  Indice_de_Cocina[0] = "MODELO     : ";
  Indice_de_Cocina[1] = "PRECIO     : S/ ";
  Indice_de_Cocina[2] = "ALTO       : ";
  Indice_de_Cocina[3] = "ANCHO      : "; 
  Indice_de_Cocina[4] = "FONDO      : ";
  Indice_de_Cocina[5] = "QUEMADORES : ";
  
  cout << "1 = Cosultar Cocina\n2 = Modificar Cocina\n3 = Lista de Cocinas\n";
  cout << "Elija la opción: ";
  cin >> Opc_Mante;
  Error_cin();
  switch(Opc_Mante) {
    case 1: cout << "\nCONSULTAR COCINA:\n\n";
      Consultar_Cocina();
      break;
    case 2: cout << "\nMODIFICAR COCINA:\n\n";
      Mostrar_Modificar_Cocina ();
      break;
    case 3: cout << "\nLISTA DE COCINAS:\n\n";
      Mostrar_Lista_de_Cocinas();
      break;
    default: Mostrar_Mensaje_de_Error();
      return Mostrar_Mantenimiento ();
      break;
    }
}

/*================MENU===================*/
int Opc_Menu;
void Mostrar_Menu () {

  cout << "\t\nLA TIENDITA DE DON PEPE\n\n";
  
  cout << "MENU\n\n";
  cout << "1 = Mantenimiento\n2 = Vender\n3 = Reportes\n4 = Configuración\n5 = Salir\n";
  cout << "Elija la opción: ";
  cin >> Opc_Menu;
  Error_cin();

  switch (Opc_Menu) {
    case 1: cout << "\nMANTENIMIENTO:\n\n";
      Mostrar_Mantenimiento ();
      cout << "\nVolviendo al menu...\n";
      return Mostrar_Menu ();
      break;
    case 2: cout << "\nVENDER:\n\n";
      Mostrar_Vender_Cocina();
      cout << "\nVolviendo al menu...\n";
      return Mostrar_Menu ();
      break;
    case 3: cout << "\nREPORTES:\n\n";
      Mostrar_Reportes();
      cout << "\nVolviendo al menu...\n";
      return Mostrar_Menu ();
    case 4: cout << "\nCONFIGURACIÓN:\n\n";
      Mostrar_Configuracion();
      cout << "\nVolviendo al menu...\n";
      return Mostrar_Menu ();
    break;
    case 5: cout << "\nSALIR\n\n";
      int Opc_Salir;
      cout << "¿Esta usted seguro de salir?\n";
      cout << "\n 1.- SI ";
      cout << "\n 2.- NO\n";
      cin >> Opc_Salir;
      if(Opc_Salir ==1) { 
        cout << "\nHasta luego, vuelva pronto ;)";
        exit(0);        
      }
      else if(Opc_Salir == 2) {
       return Mostrar_Menu ();
      }
      else {
        Mostrar_Mensaje_de_Error(); 
        return Mostrar_Menu();
      }
      break;
    default: Mostrar_Mensaje_de_Error();
      return Mostrar_Menu();
      break;
  }  
}
/*==============PRINCIPAL===============*/

int main() {

Guardar_Lista_de_Cocinas();
Guardar_Configuracion();
Mostrar_Menu();
  
return 0;
}