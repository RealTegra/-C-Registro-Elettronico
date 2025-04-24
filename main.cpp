
//Registro elettronico sviluppato da
//Monasterolo Marco

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

typedef struct alunno {
    int matricola;
    string nome;
    string cognome;
    int eta;
    int anno;
    string classe;
    bool bocciato;
}alunno;

typedef struct voto {
    int IDVoto;
    int matricola;
    string materia;
    int valutazione;
}voto;

static int IDVoto = 0;
static int matricola = 0;

int menu();
void caricaAlunno(vector<alunno> &alunni);
void cancellaAlunno(vector<alunno> &alunni, vector<voto> &voti);
void caricaVoto(vector<alunno> &alunni, vector<voto> &voti);
void modificaVoto(vector<voto> &voti);
void cancellaVoto(vector<voto> &voti);
void visualizzaAlunni(vector<alunno> &alunni);
void visualizzaVoti(vector<alunno> &alunni,vector<voto> &voti);

int main() {

    vector<alunno> alunni;
    vector<voto> voti;

    int scelta = 0;

    do {
        scelta = menu();
        switch (scelta) {
            case 1:
                caricaAlunno(alunni);
                break;
            case 2:
                cancellaAlunno(alunni, voti);
                break;
            case 3:
                caricaVoto(alunni, voti);
                break;
            case 4:
                modificaVoto(voti);
                break;
            case 5:
                cancellaVoto(voti);
                break;
            case 6:
                visualizzaAlunni(alunni);
                break;
            case 7:
                visualizzaVoti(alunni, voti);
                break;
            case 0:
                cout << "Arrivederci" << endl;
                break;
            default:
                cout << "Scelta non valida, riprova" << endl;
                break;
        }
    }
    while (scelta != 0);
}

int menu() {
    int s;
    cout << "Benvenuto nel registro elettronico, cosa vuoi fare?" << endl;
    cout << "1. Caricare un alunno" << endl;
    cout << "2. Cancellare un alunno" << endl;
    cout << "3. Caricare un voto" << endl;
    cout << "4. Modificare un voto" << endl;
    cout << "5. Cancellare un voto" << endl;
    cout << "6. Visualizza tutti gli alunni" << endl;
    cout << "7. Visualizza i voti di un alunno e la sua media totale" << endl;
    cout << "0. Esci" << endl;

    cin >> s;
    return s;
}

void caricaAlunno(vector<alunno> &alunni) {
    string nome, cognome, classe;
    int eta, anno;
    bool bocciato;

    cout << "Inserisci il nome dell'alunno" << endl;
    cin >> nome;
    cout << "Inserisci il cognome dell'alunno" << endl;
    cin >> cognome;
    cout << "Inserisci l'eta dell'alunno" << endl;
    cin >> eta;
    cout << "Inserisci l'anno di nascita dell'alunno" << endl;
    cin >> anno;
    cout << "Inserisci la classe dell'alunno" << endl;
    cin >> classe;
    cout << "L'alunno è stato bocciato? 1: Sì, 0: No " << endl;
    cin >> bocciato;

    if (nome.length() < 2) {
        cout << "Inserisci un nome valido!" << endl;
        return;
    }
    else if (cognome.length() < 2) {
        cout << "Inserisci un cognome valido!" << endl;
        return;
    }
    else if (eta < 14 || eta > 20) {
        cout << "Inserisci un'età valida! tra i 14 e 20 anni" << endl;
        return;
    }
    else if (anno < 1900 || anno > 2020) {
        cout << "Inserisci un anno di nascita valido!" << endl;
        return;
    }
    else if (classe.length() != 5) {
        cout << "Inserisci una classe valida nel seguente formato: SezioneCorsoIndirizzo (Esempio: 3CINF)" << endl;
        return;
    }

    alunno temp;
    temp.matricola = matricola;
    temp.nome = nome;
    temp.cognome = cognome;
    temp.eta = eta;
    temp.anno = anno;
    temp.classe = classe;
    temp.bocciato = bocciato;
    alunni.push_back(temp);
    matricola++;

    cout << "Alunno " << alunni.back().nome << " " << alunni.back().cognome << " caricato con successo" << endl;
}
void cancellaAlunno(vector<alunno> &alunni, vector<voto> &voti) {
    int matricola;
    cout << "Inserisci la matricola dell'alunno che vuoi cancellare" << endl;
    cin.ignore();
    cin >> matricola;

    bool ok = false;
    for (size_t j = 0; j < alunni.size(); j++) {
        if (alunni[j].matricola == matricola) {
            alunni.erase(alunni.begin() + j);
            ok = true;
            break;
        }
    }

    if (ok) {
        bool votoCancellato = false;
        for (int i = voti.size() - 1; i >= 0; i--) {
            if (voti[i].matricola == matricola) {
                voti.erase(voti.begin() + i);
                votoCancellato = true;
            }
        }

        if (!votoCancellato) {
            cout << "Nessun voto cancellato, l'alunno non aveva voti" << endl;
        }

        cout << "Alunno cancellato con successo" << endl;
    } else {
        cout << "Alunno non trovato" << endl;
    }
}

void caricaVoto(vector<alunno> &alunni, vector<voto> &voti) {
    int mat;
    cout << "Inserisci la matricola dell'alunno a cui vuoi aggiungere un voto: ";
    cin.ignore();
    cin >> mat;

    bool trovato = false;
    for (const auto &a : alunni) {
        if (a.matricola == mat) {
            trovato = true;
            break;
        }
    }

    if (!trovato) {
        cout << "Matricola non trovata. Impossibile caricare il voto." << endl;
        return;
    }

    string materia;
    int valutazione;

    cout << "Inserisci la materia: ";
    cin.ignore();
    cin >> materia;

    cout << "Inserisci la valutazione (da 1 a 10): ";
    cin.ignore();
    cin >> valutazione;

    if (valutazione < 1 || valutazione > 10) {
        cout << "Valutazione non valida. Deve essere tra 1 e 10." << endl;
        return;
    }

    voto nuovoVoto;
    nuovoVoto.IDVoto = IDVoto++;
    nuovoVoto.matricola = mat;
    nuovoVoto.materia = materia;
    nuovoVoto.valutazione = valutazione;

    voti.push_back(nuovoVoto);

    cout << "Voto caricato con successo per l'alunno con matricola " << mat << "." << endl;
}

void modificaVoto(vector<voto> &voti) {
    int id;
    cout << "Inserisci l'ID del voto che vuoi modificare: ";
    cin.ignore();
    cin >> id;

    bool trovato = false;

    for (int i = 0; i < voti.size(); i++) {
        if (voti[i].IDVoto == id) {
            trovato = true;
            cout << "Voto trovato! Materia attuale: " << voti[i].materia
                 << ", valutazione attuale: " << voti[i].valutazione << endl;

            string nuovaMateria;
            int nuovaValutazione;

            cout << "Inserisci la nuova materia (oppure premi invio per non modificarla): ";
            cin.ignore();
            cin >> nuovaMateria;

            if (!nuovaMateria.empty()) {
                voti[i].materia = nuovaMateria;
            }

            cout << "Inserisci la nuova valutazione (da 1 a 10): ";
            cin.ignore();
            cin >> nuovaValutazione;

            if (nuovaValutazione < 1 || nuovaValutazione > 10) {
                cout << "Valutazione non valida. Deve essere tra 1 e 10. Modifica annullata." << endl;
                return;
            }

            voti[i].valutazione = nuovaValutazione;

            cout << "Voto modificato con successo!" << endl;
        }
    }

    if (!trovato) {
        cout << "Voto con ID " << id << " non trovato." << endl;
    }
}

void cancellaVoto(vector<voto> &voti) {
    int id;
    cout << "Inserisci l'ID del voto che vuoi cancellare: ";
    cin >> id;

    bool trovato = false;

    for (int i = 0; i < voti.size(); i++) {
        if (voti[i].IDVoto == id) {
            voti.erase(voti.begin() + i);
            trovato = true;
            cout << "Voto cancellato con successo!" << endl;
            break;
        }
    }

    if (!trovato) {
        cout << "Voto con ID " << id << " non trovato." << endl;
    }
}

void visualizzaAlunni(vector<alunno> &alunni) {
    if (alunni.empty()) {
        cout << "Nessun alunno presente." << endl;
        return;
    }

    cout << "\nLista degli alunni:\n";
    for (int i = 0; i < alunni.size(); i++) {
        cout << "Matricola: " << alunni[i].matricola << endl;
        cout << "Nome: " << alunni[i].nome << " " << alunni[i].cognome << endl;
        cout << "Eta: " << alunni[i].eta << " anni" << endl;
        cout << "Anno di nascita: " << alunni[i].anno << endl;
        cout << "Classe: " << alunni[i].classe << endl;
        cout << "Bocciato: " << (alunni[i].bocciato ? "Sì" : "No") << endl;
        cout << "-----------------------------" << endl;
    }
}

void visualizzaVoti(vector<alunno> &alunni, vector<voto> &voti) {
    int mat;
    cout << "Inserisci la matricola dell'alunno: ";
    cin >> mat;

    bool alunnoTrovato = false;
    string nome, cognome;

    int i = 0;
    while (i < alunni.size() && !alunnoTrovato) {
        if (alunni[i].matricola == mat) {
            alunnoTrovato = true;
            nome = alunni[i].nome;
            cognome = alunni[i].cognome;
        }
        i++;
    }

    if (!alunnoTrovato) {
        cout << "Alunno non trovato." << endl;
        return;
    }

    cout << "\nVoti dell'alunno " << nome << " " << cognome << " (Matricola: " << mat << "):" << endl;

    int somma = 0;
    int conteggio = 0;

    int j = 0;
    while (j < voti.size()) {
        if (voti[j].matricola == mat) {
            cout << "Materia: " << voti[j].materia << " | Valutazione: " << voti[j].valutazione << endl;
            somma += voti[j].valutazione;
            conteggio++;
        }
        j++;
    }

    if (conteggio == 0) {
        cout << "Nessun voto registrato per questo alunno." << endl;
    } else {
        double media = static_cast<double>(somma) / conteggio;
        cout << "Media totale: " << media << endl;
    }
}


