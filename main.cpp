#include <iostream>
#include <fstream>//uso de .txt
#include <string>
#include <string.h>

using namespace std;

string Cocinas[6][6], indice[6];
int N_Boleto = 0, cant_ventas[5], Vec_T_unidades[5];
float Importe_t_pagar[5], Configuracion_tienda[4];

/*===========GUARDAR_DATOS============*/

void Guardar_Lista_de_Cocinas() {
  string s1[6], s2[6];
  ifstream Lista_Cocinas;
  Lista_Cocinas.open("cocina-data.txt");
  if (!Lista_Cocinas.is_open()) {
    cout << "Error" << endl;
  }
  //ASIGNACION+1
  for (int i = 0; i < 6; i++) {
    Lista_Cocinas >> s1[i] >> s2[i];
    for (int j = 0; j < 5; j++){
      Lista_Cocinas >> Cocinas[i][j+1];
    }
  }
  for (int i = 0; i < 6; i++) {
    Cocinas[i][0] = s1[i] + " " + s2[i];
  }   
Lista_Cocinas.close();
}

void Guardar_Configuracion() {
  ifstream Configuracion;
  Configuracion.open("config-tienda.txt");
  if (Configuracion.is_open()) {
    for (int i = 0; i < 4; i++) {
      Configuracion >> Configuracion_tienda[i];
 //     if (i < 3){
 //       Configuracion_tienda[i] = Configuracion_tienda[i] / 100;
//      }
    }   
    
  Configuracion.close();
  }
}



void DESCRIBE(int x) {
  for (int j = 1; j < 6; j++) {
    cout << indice[j] << Cocinas[x][j] << endl;
  }
}

/* ==========CONFIGURACION========== */

void Cofigurar_cantidad_optima() {
  cout << "Cantidad optima actual: " << Configuracion_tienda[3] << endl;
  cout << "Indique la nueva cantidad optima: ";
  cin >> Configuracion_tienda[3];
  
}

void Configurar_descuentos() {
  int Opc_Dsc = 0;
  for (int i = 0; i < 3; i++) {
    cout << i+1 << "= Descuento " << i + 1 << " : " << Configuracion_tienda[i] << endl;
    }
  cout << "\nIndique el descuento a modificar: ";
  cin >> Opc_Dsc;
  cout << endl;
  if (Opc_Dsc > 0 && Opc_Dsc < 4) {
    cout << "Indique el nuevo descuento: ";
    cin >> Configuracion_tienda[Opc_Dsc-1];
  }
  else {
    cout << "Error, la opcion elegida es incorrecta. Vuelva a elegir" << endl << endl;
    return Configurar_descuentos();
  }
}

  
/*============REPORTES==============*/

void Reportes_Ventas_relacion_a_venta_optima() {
  
  cout << "VENTAS EN RELACIÓN A LA VENTA OPTIMA" << endl << endl;
  //ifstream Cantidad_optima;
  //Cantidad_optima.open("config-tienda.txt");

  for (int i = 0; i < 5; i++) {
    cout << "Modelo             :  " << Cocinas[i][0] << endl;
    cout << "Unidades vendidas  :  " << Vec_T_unidades[i] << " (";
    
    if (Configuracion_tienda[3] > Vec_T_unidades[i]) {
      cout << Configuracion_tienda[3] - Vec_T_unidades[i] << " mas";
    }
    else if (Configuracion_tienda[3] < Vec_T_unidades[i]) {
      cout << Configuracion_tienda[3] - Vec_T_unidades[i] << " menos";
    }
    else if (Configuracion_tienda[3] == Vec_T_unidades[i]){
      cout << " igual";
    } 
    cout << " que la cantidad optima)" << endl << endl;
  }

  
}

void Reportes_Ventas_por_modelo() {
cout << "VENTAS POR MODELO" << endl << endl;
for (int i = 0; i < 5; i++){
  cout << "Modelo                         :  " << Cocinas[i][0] << endl;
  cout << "Cantidad de ventas             :  " << cant_ventas[i] << endl;
  cout << "Cantidad de unidades vendidas  :  " << Vec_T_unidades[i] << endl;
  cout << "Importe total vendido          :  " << Importe_t_pagar[i] << endl << endl;
}

  
}


  
/*============VENDER================*/

void VENDER(int Nr_Cocina, int Total_U_Vendidas[5]) {
  int cant_vent = 0;
  float importe_compras, importe_pagar, x, descuento;
  string num_str1(to_string(N_Boleto));
  ofstream boletas;
  
  cout << "Elija la cantidad de cocinas a comprar: ";
  cin >> cant_vent;
  
  Total_U_Vendidas[Nr_Cocina]  = cant_vent +  Total_U_Vendidas[Nr_Cocina];
  
  x = stof(Cocinas[Nr_Cocina][1]);
  importe_compras = cant_vent * x;

  if (cant_vent >= 1 && cant_vent < 6) {
    descuento = importe_compras * (Configuracion_tienda[0]/100);
  }
  else if (cant_vent > 5 && cant_vent < 11) {
    descuento = importe_compras * (Configuracion_tienda[1]/100);
  }
  else if (cant_vent > 9) {
    descuento = importe_compras * (Configuracion_tienda[2]/100);
  }
   else {
    cout << "Revise que la cantidad sea positiva y un entero" << endl;
     
   }
  importe_pagar = importe_compras - descuento;
  Importe_t_pagar[Nr_Cocina] = importe_pagar + Importe_t_pagar[Nr_Cocina];
  
  boletas.open("boleta_<" + num_str1 + ">.txt");
  
  if (boletas.is_open()) {
    boletas << "BOLETA DE VENTA: " << N_Boleto << endl << endl;
    boletas << "Modelo         : " << Cocinas[Nr_Cocina][0] << endl;
    boletas << "Precio         : " << "S/ " << Cocinas[Nr_Cocina][1] << endl;
    boletas << "Cantidad       : " << cant_vent << endl;
    boletas << "Importe compra : " << "S/ " << importe_compras << endl;
    boletas << "Descuento      : " << "S/ " << descuento << endl;
    boletas << "Importe pagar  : " << "S/ " << importe_pagar << endl;
        
    boletas.close();
        
    }
  N_Boleto ++;
  
}

void Vender_Cocina() {
  int opcion_Cons, *Pcan_Ventas;
  cout << "¿Qué modelo desea comprar?\n";
  cout << "1 = Mabe EMP6120PG0\n2 = Indurama Parma\n3 = Sole COSOL027\n4 = Coldex CX602\n5 = Reco Dakota\n";
  cout << "Elija la opcion: ";
  cin >> opcion_Cons;
  cout << endl;
  
  switch(opcion_Cons){
    case 1: cout << "Cocina 1:\n\n";
      VENDER(opcion_Cons-1, &Vec_T_unidades[0]);
      cant_ventas[0]++;
    break;
    case 2: cout << "Cocina 2:\n\n";
      VENDER(opcion_Cons-1, &Vec_T_unidades[1]);
      cant_ventas[1]++;
    break;
    case 3: cout << "Cocina 3:\n\n";
      VENDER(opcion_Cons-1, &Vec_T_unidades[2]);
      cant_ventas[2]++;
    break;
    case 4: cout << "Cocina 4:\n\n";
      VENDER(opcion_Cons-1, &Vec_T_unidades[3]);
      cant_ventas[3]++;
    break;
    case 5: cout << "Cocina 5:\n\n";
      VENDER(opcion_Cons-1, &Vec_T_unidades[4]);
      cant_ventas[4]++;
    break;
  } 
}





/*============MANTENIMIENTO==========*/

void Opcion_Modificar_Cocina(int x) {
  int b;
  int a;
  int opcion;
  cout << "\n ¿Desea modificar por partes o todo?" << endl;
  cout << "\n 1.- Por partes ";
  cout << "\n 2.- Todo ";
  cout << "\n 3.- N/A\n";
  cin >> a;
  if(a == 1){
    cout << "Elija que deseea moficar:\n1 = PRECIO\n2 = ALTO\n3 = ANCHO\n4 = FONDO\n5 = QUEMDORES\n";
    cin >> opcion;
    cout << endl;
    switch (opcion){
      case 1:
        cout << "Indique el nuevo precio\n";
        cin >> Cocinas[x][1];
      break;
      case 2:
        cout << "Indique el alto\n";
        cin >> Cocinas[x][2];
      break;
      case 3:
        cout << "Indique el nuevo ancho\n";
        cin >> Cocinas[x][3];
      break;
      case 4:
        cout << "Indique el nuevo fondo\n";
        cin >> Cocinas[x][4];
      break;
      case 5:
        cout << "Indique catidad de quemadores\n";
        cin >> Cocinas[x][5];
      break;
      default: cout << "ERROR MI CAUSITA, QUE PASA AH" << endl;
    break;
    }
  }
  else if(a==2){
    cout << "\nIndique el nuevo precio\n";
    cin >> Cocinas[x][1];
    cout << "Indique el alto\n";
    cin >> Cocinas[x][2];
    cout << "Indique el nuevo fondo\n";
    cin >> Cocinas[x][3];
    cout << "Indique el nuevo fondo\n";
    cin >> Cocinas[x][4];
    cout << "Indique catidad de quemadores\n";
    cin >> Cocinas[x][5];
  }
  else if(a==3){
    
  }

  cout << "¿Esta correcto?\n";
  for (int j = 1; j < 6; j++) {
    cout << indice[j] <<  Cocinas[x][j] << endl;
  }
  cout << "\n 1.- SI ";
  cout << "\n 2.- NO\n";
  cin >> b;
  cout << "\n";
  if(b==2){
  
  }

  cout << "\n ¿Desea Volver a modificar?" << endl;
  cout << "\n 1.- SI ";
  cout << "\n 2.- NO\n";
  cin >> b;
  cout << "\n";
  if(b==1){
    return Opcion_Modificar_Cocina(x);
  }
  else {
    
  }
}

void Modificar_Cocina () {
  int opcion_mod;
  int b;
  cout<< "Elija cocina a modificar\n1 = Mabe EMP6120PG0\n2 = Indurama Parma\n3 = Sole COSOL027\n4 = Coldex CX602\n5 = Reco Dakota\n ";
  cout << "Elija la opcion\n";
  cin >> opcion_mod;
  cout << "\n";
    switch(opcion_mod){
      case 1: 
      Opcion_Modificar_Cocina(0);
      break;
      case 2: 
      Opcion_Modificar_Cocina(1);
      break;
      case 3: 
      Opcion_Modificar_Cocina(2);
      break;
      case 4: 
      Opcion_Modificar_Cocina(3);
      break;
      case 5:  
      Opcion_Modificar_Cocina(4);
       break;
  } 
}

void Lista_de_Cocinas () {
  fstream Lista_Cocinas;
  Lista_Cocinas.open("cocina-data.txt",ios::in);
  if(Lista_Cocinas.is_open()) {
    string tp;
    int cont = 1;
    int cont1 = 0;
    while (getline(Lista_Cocinas, tp)) {       
      if (cont1 < 6) {
      cout << indice[cont1];
      cont1++;
      }
      cout << tp << "\n";
      cont ++;
      if (cont > 6) {
        cout << "============================\n";
        cont = 1;
        cont1 = 0;
      }
    } 
  Lista_Cocinas.close();
  }
}

void Consultar_Cocina () {
  int opcion_Cons;
  cout << "1 = Mabe EMP6120PG0\n2 = Indurama Parma\n3 = Sole COSOL027\n4 = Coldex CX602\n5 = Reco Dakota\n";
  cout << "Elija la opcion: ";
  cin >> opcion_Cons;
  cout << "\n";
  
  switch(opcion_Cons){
    case 1: cout << "Cocina 1:\n\n";
    DESCRIBE(0);
    break;
    case 2: cout << "Cocina 2:\n\n";
    DESCRIBE(1);
    break;
    case 3: cout << "Cocina 3:\n\n";
    DESCRIBE(2);
    break;
    case 4: cout << "Cocina 4:\n\n";
    DESCRIBE(3);
    break;
    case 5: cout << "Cocina 5:\n\n";
    DESCRIBE(4);
    break;
  } 
}

void Mostrar_Mantenimiento () {
  
  int opcion_Mant;
  indice[0] = "MODELO     : ";
  indice[1] = "PRECIO     : ";
  indice[2] = "ALTO       : ";
  indice[3] = "ANCHO      : "; 
  indice[4] = "FONDO      : ";
  indice[5] = "QUEMADORES : ";
  
  
  cout << "1 = Cosultar Cocina\n2 = Modificar Cocina\n3 = Lista de Cocinas\n";
  cout << "Elija la opción: ";
  cin >> opcion_Mant;
  cout << "\n";
  
    switch(opcion_Mant) {
      case 1: cout << "Cosultar Cocina\n";
      Consultar_Cocina();
      break;
      case 2: cout << "Modificar Cocina\n";
      Modificar_Cocina ();
      break;
      case 3: cout << "\tLista de Cocinas: \n";
      cout<<"============================\n";
      Lista_de_Cocinas();
      break;
    }
}

/*===================================*/
void Mostrar_Menu () {
  int opcion;
  
  cout << "\tTIENDITA DE DON PEPE" << endl;
  cout << "MENU: " << endl;
  cout << "1 = Mantenimiento\n2 = Vender\n3 = Reportes\n4 = Configuración\n5 = Salir\n";
  
  cout << "Elija la opción: ";
  cin >> opcion;
  cout << endl;
  
  switch (opcion) {
    case 1: cout << "\nMANTENIMIENTO:" << endl;
      Mostrar_Mantenimiento ();
    break;
    case 2: cout << "\nVENDER" << endl;
      Vender_Cocina();
    break;
    case 3: cout << "\nREPORTES:" << endl;
      int Opc_Reportes;
      cout << "1=Ventas por modelo\n2=Ventas en relación a la venta óptima\n";
      cout << "Elija la opción: ";
      cin >> Opc_Reportes;
      cout << endl;
      switch (Opc_Reportes) {
        case 1: Reportes_Ventas_por_modelo();
        break;
        case 2: Reportes_Ventas_relacion_a_venta_optima();
        break;
      }
    break;
    case 4: cout << "\nCONFIGURACIÓN:" << endl;
     int Opc_Configuracion;
      cout << "1=Cofigurar_descuentos\n2=Cofigurar_cantidad_optima\n";
      cout << "Elija la opción: ";
      cin >> Opc_Configuracion;
      cout << endl;
      switch (Opc_Configuracion) {
        case 1: Configurar_descuentos();
        break;
        case 2: Cofigurar_cantidad_optima();
        break;
      }
    break;
    case 5: cout << "\nSALIR:" << endl;
      int Opc_Salir;
      cout << "¿Esta usted seguro de salir?\n";
        cout << "\n 1.- SI ";
        cout << "\n 2.- NO\n";
        cin >> Opc_Salir;
        cout << "\n";
        if(Opc_Salir ==1){ 
            cout << "\nHasta luego, vuelva pronto ;)";
           exit(0);        
        }
        else if(Opc_Salir == 2){
          return Mostrar_Menu();
        }
        else {
          cout << "La opcion marcada no existe, volviendo al Menú..." << endl << endl;
          return Mostrar_Menu();
        }
    break;
  }
}



int main() {

Guardar_Lista_de_Cocinas();
Guardar_Configuracion();
Mostrar_Menu();
  
return 0;
}