#include "fenetre.h"

Fenetre::Fenetre(const wxString &title, Jeu jeu)
		: wxFrame(NULL, wxID_ANY, title,
							wxDefaultPosition,
							wxSize(1000, 1000), wxDEFAULT_FRAME_STYLE),
			_jeu(jeu)
{
	btnStart = new wxButton(this, BUTTON_start, wxT("Start"), wxPoint(20, 20), wxDefaultSize);
	btnStop = new wxButton(this, BUTTON_stop, wxT("Stop"), wxPoint(20, 60), wxDefaultSize);
	btnClear = new wxButton(this, BUTTON_clear, wxT("Clear"), wxPoint(20, 100), wxDefaultSize);

	////////////////PARTIE MENU BAR//////////////////////////////
	menubar = new wxMenuBar;
	select = new wxMenu;
	stable = new wxMenu;
	period = new wxMenu;
	vaisseau = new wxMenu;
	autres = new wxMenu;
	infini = new wxMenuItem(select, INFINI, wxT("Infini"));

	// Creation des submenus
	stable->Append(STABLE_BLOC, wxT("Bloc"));
	stable->Append(STABLE_TUBE, wxT("Tube"));
	stable->Append(STABLE_BATEAU, wxT("Bateau"));
	stable->Append(STABLE_RUCHE, wxT("Ruche"));
	stable->Append(STABLE_HAMECON, wxT("Hamecon"));

	period->Append(PERIOD_CLIG, wxT("Clignotant"));
	period->Append(PERIOD_HORLOGE, wxT("Horloge"));
	period->Append(PERIOD_PENTA, wxT("Pentadecathlon"));
	period->Append(PERIOD_GALAXIE, wxT("Galaxie"));

	vaisseau->Append(V_GLISS, wxT("Glisseur"));
	vaisseau->Append(V_LEGER, wxT("Vaisseau leger"));

	autres->Append(A_R, wxT("Pentamino R"));
	autres->Append(A_U, wxT("U"));

	// Ajouter des submenus dans le main menu
	select->AppendSubMenu(stable, wxT("Stable"));
	select->AppendSubMenu(period, wxT("Period"));
	select->AppendSubMenu(vaisseau, wxT("Vaisseau"));
	select->AppendSubMenu(autres, wxT("Autres"));
	select->Append(infini);

	// Ajouter le main menu dans le menu bar
	menubar->Append(select, wxT("&SELECT"));
	SetMenuBar(menubar);

	// Creation des "event handler" pour traiter chaque option dans le menu bar
	// Chauque methode va ajouter des cellules necessaires
	Connect(STABLE_BLOC, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnBloc));
	Connect(STABLE_TUBE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnTube));
	Connect(STABLE_BATEAU, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnBateau));
	Connect(STABLE_RUCHE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnRuche));
	Connect(STABLE_HAMECON, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnHamecon));
	Connect(PERIOD_CLIG, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnClig));
	Connect(PERIOD_HORLOGE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnHorloge));
	Connect(PERIOD_PENTA, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnPenta));
	Connect(PERIOD_GALAXIE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnGalaxie));
	Connect(V_GLISS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnGliss));
	Connect(V_LEGER, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnLeger));
	Connect(A_R, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnR));
	Connect(A_U, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnU));
	Connect(INFINI, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Fenetre::OnInfini));
	////////////////FIN PARTIE MENU BAR//////////////////////////////
}

BEGIN_EVENT_TABLE(Fenetre, wxFrame)
EVT_BUTTON(BUTTON_start, Fenetre::OnStart)
EVT_BUTTON(BUTTON_stop, Fenetre::OnStop)
EVT_BUTTON(BUTTON_clear, Fenetre::OnClear)
EVT_PAINT(Fenetre::OnPaint)
EVT_LEFT_UP(Fenetre::OnLeftClick)
END_EVENT_TABLE()

void Fenetre::OnStart(wxCommandEvent &ev)
{
	wxGetApp().RenderLoopOn();
}
void Fenetre::OnStop(wxCommandEvent &ev)
{
	wxGetApp().RenderLoopOff();
}
// Creer une grille nouvelle
void Fenetre::OnClear(wxCommandEvent &ev)
{
	Grille grille(50, 80);
	Jeu new_jeu(grille);
	_jeu = new_jeu;
	TriggerPaint();
}

// Dessiner la grille + des cellules
// La grille est fixee de taille 50,80 ; chaque carree est de taille 20,20
// La grille commene aux coord (200,20)
void Fenetre::OnPaint(wxPaintEvent &ev)
{
	wxPaintDC dc(this);
	for (int i = 0; i < _jeu.getRow(); i++)
	{
		for (int j = 0; j < _jeu.getColumn(); j++)
		{
			dc.DrawRectangle(200 + 20 * j, 20 + 20 * i, 20, 20);
			if (_jeu.estOccupee(i, j))
			{
				dc.SetBrush(*wxBLUE_BRUSH);
				dc.DrawCircle(210 + 20 * j, 30 + 20 * i, 10);
				dc.SetBrush(*wxWHITE_BRUSH);
			}
		}
	}
}

void Fenetre::TriggerPaint()
{
	Refresh();
}

// Cliquer pour ajouter/supprimer
void Fenetre::OnLeftClick(wxMouseEvent &ev)
{
	int x, y;
	// x,y contiennent les coords du clique
	ev.GetPosition(&x, &y);
	int i, j;
	// Comme on commence a (200,20) et chauque carree est de taille 20,20
	// On peut retrouver les coords de la grille en calculer l'inverse
	// La division entiere va caculer exactement cela
	// EX: souris clique sur (532,67) -> j = 16.6 et i =  2.35 -> Division entiere j = 16 et i = 2
	// Le point que le souris a clique sur est le point (16,2)
	j = (x - 200) / 20;
	i = (y - 20) / 20;
	int m = _jeu.getRow();
	int n = _jeu.getColumn();
	if ((i >= 0) && (i < m) && (j >= 0) && (j < n))
	{
		if (_jeu.estOccupee(i, j))
		{
			_jeu.SupprimeCellule(i, j);
		}
		else
		{
			_jeu.AjouteCellule(i, j);
		}
		TriggerPaint();
	}
}

//METHODE POUR MENUBAR//
// x est le vecteur des coords horizontales
// y est le vecteur des coords verticales
void Fenetre::OnBloc(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{25, 25, 26, 26};
	std::vector<int> y{25, 26, 25, 26};
	Fenetre_Add(x, y);
}
void Fenetre::OnTube(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{21, 22, 23, 22};
	std::vector<int> y{35, 34, 35, 36};
	Fenetre_Add(x, y);
}
void Fenetre::OnBateau(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{26, 26, 27, 28, 27};
	std::vector<int> y{34, 35, 34, 35, 36};
	Fenetre_Add(x, y);
}
void Fenetre::OnRuche(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{26, 27, 28, 29, 28, 27};
	std::vector<int> y{36, 35, 35, 36, 37, 37};
	Fenetre_Add(x, y);
}
void Fenetre::OnHamecon(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{26, 26, 27, 28, 29, 29, 28};
	std::vector<int> y{31, 32, 32, 32, 33, 34, 34};
	Fenetre_Add(x, y);
}
void Fenetre::OnClig(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{24, 25, 26};
	std::vector<int> y{36, 36, 36};
	Fenetre_Add(x, y);
}
void Fenetre::OnHorloge(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{22, 22, 23, 23, 22, 23, 24, 25, 26, 26, 26, 26, 25, 24, 23, 22, 21, 21, 21, 21, 19, 19, 18, 18, 24, 25, 25, 24, 28, 28, 29, 29, 23, 24, 24};
	std::vector<int> y{27, 26, 26, 27, 29, 29, 29, 29, 30, 31, 32, 33, 34, 34, 34, 34, 33, 32, 31, 30, 32, 33, 33, 32, 36, 36, 37, 37, 30, 31, 30, 31, 30, 31, 32};
	Fenetre_Add(x, y);
}
void Fenetre::OnPenta(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{19, 19, 20, 20, 21, 21, 22, 23, 24, 22, 23, 24, 25, 26, 27, 27, 26, 25};
	std::vector<int> y{35, 36, 33, 38, 32, 39, 31, 31, 31, 40, 40, 40, 32, 33, 35, 36, 38, 39};
	Fenetre_Add(x, y);
}
void Fenetre::OnGalaxie(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{15, 16, 17, 18, 19, 20, 15, 16, 17, 18, 19, 20, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 18, 19, 20, 21, 22, 23, 18, 19, 20, 21, 22, 23, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23};
	std::vector<int> y{25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 28, 29, 30, 31, 32, 33, 28, 29, 30, 31, 32, 33, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 25, 26, 27, 28, 29, 30, 25, 26, 27, 28, 29, 30};
	Fenetre_Add(x, y);
}
void Fenetre::OnGliss(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{14, 15, 16, 16, 16};
	std::vector<int> y{27, 28, 28, 27, 26};
	Fenetre_Add(x, y);
}
void Fenetre::OnLeger(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{14, 15, 16, 17, 17, 14, 16, 17, 17, 16, 15, 14};
	std::vector<int> y{27, 28, 28, 27, 26, 24, 24, 25, 28, 28, 28, 27};
	Fenetre_Add(x, y);
}
void Fenetre::OnR(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{22, 23, 24, 24, 23};
	std::vector<int> y{35, 35, 35, 34, 36};
	Fenetre_Add(x, y);
}
void Fenetre::OnU(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{24, 25, 26, 26, 26, 25, 24};
	std::vector<int> y{33, 33, 33, 34, 35, 35, 35};
	Fenetre_Add(x, y);
}
void Fenetre::OnInfini(wxCommandEvent &WXUNUSED(ev))
{
	std::vector<int> x{4, 4, 5, 5, 4, 5, 6, 3, 7, 2, 2, 8, 8, 3, 4, 5, 6, 7, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 5, 5, 6, 2, 2, 3, 3};
	std::vector<int> y{0, 1, 1, 0, 10, 10, 10, 11, 11, 12, 13, 12, 13, 15, 16, 16, 16, 15, 17, 14, 20, 21, 20, 21, 21, 20, 22, 24, 24, 22, 24, 24, 34, 35, 35, 34};
	Fenetre_Add(x, y);
}

// Etant donne les 2 vecteurs x et y, ajouter des cellules correspondantes
void Fenetre::Fenetre_Add(std::vector<int> x, std::vector<int> y)
{
	for (int index = 0; index < x.size(); index++)
	{
		_jeu.AjouteCellule(x[index], y[index]);
	}
	TriggerPaint();
}
