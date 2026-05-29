#include <iostream>
using namespace std;


// Struct User (Iven Louis Harijaya Pane / 255150300111015)
struct User{
	string id;
	string nama;
	float temperature;
	float humidity;
	int airQuality;
	bool smoke;
	float noise;
	float score;
	User *next;
};

User *head = NULL;

// Validasi ID User (Iven Louis Harijaya Pane / 255150300111015)
bool validPrefix(string id){
	if(id.length() < 4){
		return false;
	}
	
	string prefix = id.substr(0,3);
	return (
		prefix == "013" || prefix == "015" || prefix == "017" || prefix == "026"
	);
}

// Cek ID Duplikat (Iven Louis Harijaya Pane / 255150300111015)
bool idSudahAda(string id){
	User *temp = head;
	while(temp != NULL){
		if(temp->id == id){
			return true;
		}
		temp = temp->next;
	}
	return false;
}

// Hitung Monitoring Score (Iven Louis Harijaya Pane / 255150300111015)
float hitungScore(float t, float h, int aq, bool s, float n){
	int ideal = 0;
	if(t >= 20 && t <= 27) ideal++;
	if(h>= 40 && h <=60) ideal++;
	if(aq >= 0 && aq <= 50) ideal++;
	if(s == 0) ideal++;
	if(n >=30 && n <= 55) ideal++;
	return (ideal / 5.0) * 100;
}

// Requirement 1: Insert User (Iven Louis Harijaya Pane / 255150300111015)
void insertUser(string id, string nama, float t, float h, int aq, bool s, float n){
	// Validasi awalan ID
	if(!validPrefix(id)){
		cout << "Prefix ID tidak valid!\n";
		return;
	}
	
	// Validasi ID duplikat
	if(idSudahAda(id)){
		cout << "ID sudah digunakan!\n";
		return;
	}
	
	// Validasi masing-masing sensor
	if(t < -10 || t > 50){
		cout << "Temperature tidak valid.\n";
		return;
	}
	if(h < 0 || h > 100){
		cout << "Humidity tidak valid.\n";
		return;
	}
	if(aq < 0 || aq > 500){
		cout << "Air quality tidak valid.\n";
		return;
	}
	if(n < 0 || n > 120){
		cout << "Noise tidak valid.\n";
		return;
	}
	
	User *baru = new User;
	baru->id = id;
	baru->nama = nama;
	baru->temperature = t;
	baru->humidity = h;
	baru->airQuality = aq;
	baru->smoke = s;
	baru->noise = n;
	baru->score = hitungScore(t, h, aq, s, n);
	
	baru->next = NULL;
	if(head == NULL){
		head = baru;
	} else{
		baru->next = head;
		head = baru;
	}
	
	cout << "Berhasil menambahkan pelanggan baru\n";
	cout << "User ID: " << id << endl;
	cout << "Nama	: " << nama << endl;
	cout << "Score	: " << baru->score << "%" << endl;
}

// Requirement 2: Mencari User (Aurel Aprila A.Y.P/255150307111026)
void cariUser(string id){
	if(head == NULL){
		cout << "Data kosong.\n";
		return;
	}
	
	User *temp = head;
	
	while(temp != NULL){
		if(temp->id == id){
			cout << "User ditemukan\n";
			cout << "User ID\t\t: " << temp->id << endl;
			cout << "Nama Pelanggan\t: " << temp->nama << endl;
			cout << "Monitoring Score: " << temp->score << "%" << endl;
			cout << "Temperature\t: " << temp->temperature << endl;
			cout << "Humidity\t: " << temp->humidity << endl;
			cout << "Air Quality\t: " << temp->airQuality << endl;
			cout << "Smoke\t\t: " << temp->smoke << endl;
			cout << "Noise\t\t: " << temp->noise << endl;
			return;
		}
		
		temp = temp->next;
	}
	
	cout << "User tidak ditemukan.\n";
}

// Requirement 3: Update User (RAHANDHIKA KEYSHA NOVAL PUTRA PRATAMA / 255150301111013)
void updateUserData(string targetId){
	User* current = head;
	bool found = false;
	while(current != NULL){
		if(current->id == targetId){
			found = true;
			break;
		}
		current = current->next;
	}
	if(!found){
		cout << "User not found\n";
		return;
	}
	cout << "User found\n";

	string newNama;
	float newTemp, newHum, newNoise;
	int newAQ;
	bool newSmoke;

	cin.ignore();
	cout << "Masukkan Nama Pelanggan Baru: ";
	getline(cin, newNama);
	cout << "Masukkan Temperature Baru (-10 s/d 50): ";
	cin >> newTemp;
	cout << "Masukkan Humidity Baru (0 s/d 100): ";
	cin >> newHum;
	cout << "Masukkan Air Quality Baru (0 s/d 500): ";
	cin >> newAQ;
	cout << "Masukkan Smoke Baru (0/1): ";
	cin >> newSmoke;
	cout << "Masukkan Noise Baru (0 s/d 120): ";
	cin >> newNoise;

	if(newTemp < -10.0f || newTemp > 50.0f ||
	   newHum < 0.0f || newHum > 100.0f ||
	   newAQ < 0 || newAQ > 500 ||
	   newNoise < 0.0f || newNoise > 120.0f){
		cout << "Error: Input data sensor di luar range yang valid!\n";
		return;
	}

	current->nama = newNama;
	current->temperature = newTemp;
	current->humidity = newHum;
	current->airQuality = newAQ;
	current->smoke = newSmoke;
	current->noise = newNoise;
	current->score = hitungScore(newTemp, newHum, newAQ, newSmoke, newNoise);

	cout << "New Monitoring Score: " << current->score << "%\n";
}

// Requirement 4: Delete User (RAHANDHIKA KEYSHA NOVAL PUTRA PRATAMA / 255150301111013)
void deleteUser(string id){
	if(head == NULL){
		cout << "Data kosong.\n";
		return;
	}
	
	User *curr = head;
	User *prev = NULL;
	while(curr != NULL){
		if(curr->id == id){
			if(prev == NULL){
				head = curr->next;
			} else{
				prev->next = curr->next;
			}
			delete curr;
			cout << "User berhasil dihapus.\n";
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	cout << "User tidak ditemukan.\n";
}

// Requirement 5: Show Semua User (Romy Aprilian Hermawan / 255150301111017)
// Sorting ascending by score (Selection Sort)
void sortByScore(User** arr, int n){
	for(int i = 0; i < n-1; i++){
		int minIdx = i;
		for(int j = i+1; j < n; j++){
			if(arr[j]->score < arr[minIdx]->score){
				minIdx = j;
			}
		}
		User* temp = arr[minIdx];
		arr[minIdx] = arr[i];
		arr[i] = temp;
	}
}

// Tampilkan semua user (Romy Aprilian Hermawan / 255150301111017)
void showAll(){
	if(head == NULL){
		cout << "Data kosong.\n";
		return;
	}

	// Hitung total user
	int total = 0;
	User *temp = head;
	while(temp != NULL){
		total++;
		temp = temp->next;
	}

	// Masukkan ke array pointer untuk sorting
	User** arr = new User*[total];
	temp = head;
	for(int i = 0; i < total; i++){
		arr[i] = temp;
		temp = temp->next;
	}

	// Sort ascending by score
	sortByScore(arr, total);

	// Hitung statistik
	float totalScore = 0;
	int idealCount = 0;
	int rekapTemp = 0, rekapHum = 0, rekapAQ = 0, rekapSmoke = 0, rekapNoise = 0;

	for(int i = 0; i < total; i++){
		totalScore += arr[i]->score;
		if(arr[i]->score == 100) idealCount++;

		if(arr[i]->temperature >= 20 && arr[i]->temperature <= 27) rekapTemp++;
		if(arr[i]->humidity >= 40 && arr[i]->humidity <= 60) rekapHum++;
		if(arr[i]->airQuality >= 0 && arr[i]->airQuality <= 50) rekapAQ++;
		if(arr[i]->smoke == 0) rekapSmoke++;
		if(arr[i]->noise >= 30 && arr[i]->noise <= 55) rekapNoise++;
	}

	float rataRata = totalScore / total;

	// Tampilan laporan
	cout << "==============================================\n";
	cout << "          LAPORAN MONITORING IOT\n";
	cout << "==============================================\n";
	cout << "Statistik Monitoring\n";
	cout << "Jumlah User Dengan Pembacaan Ideal      : " << idealCount << "\n";
	cout << "Jumlah User Dengan Pembacaan Tidak Ideal: " << (total - idealCount) << "\n";
	cout << "Total Pelanggan                         : " << total << "\n";
	cout << "Rata-rata Score                         : " << rataRata << "%\n";
	cout << "==============================================\n";
	cout << "Rekap Sensor\n";
	cout << "Temperature : " << rekapTemp  << " rumah\n";
	cout << "Humidity    : " << rekapHum   << " rumah\n";
	cout << "Air Quality : " << rekapAQ    << " rumah\n";
	cout << "Smoke       : " << rekapSmoke << " rumah\n";
	cout << "Noise       : " << rekapNoise << " rumah\n";

	// Tampilan peringkat
	for(int i = 0; i < total; i++){
		// Tentukan wilayah
		int wilayah = 0;
		string prefix = arr[i]->id.substr(0,3);
		if(prefix == "013") wilayah = 1;
		else if(prefix == "015") wilayah = 2;
		else if(prefix == "017") wilayah = 3;
		else if(prefix == "026") wilayah = 4;

		cout << "==============================================\n";
		cout << "Peringkat " << (i+1) << "\n";
		cout << "User ID          : " << arr[i]->id << "\n";
		cout << "Nama Pelanggan   : " << arr[i]->nama << "\n";
		cout << "Monitoring Score : " << arr[i]->score << "%\n";
		cout << "Wilayah          : " << wilayah << "\n";
		cout << "Data Sensor\n";
		cout << "*Temp        : " << arr[i]->temperature << "C\n";
		cout << "*Humidity    : " << arr[i]->humidity << "%\n";
		cout << "*Air Quality : " << arr[i]->airQuality << "\n";
		cout << "*Smoke       : " << arr[i]->smoke << "\n";
		cout << "*Noise       : " << arr[i]->noise << "dB\n";
	}
	cout << "==============================================\n";

	delete[] arr;
}

//  MENU UTAMA
void tampilMenu(){
	cout << "==============================================\n";
	cout << "       SISTEM MONITORING RUMAH IoT\n";
	cout << "==============================================\n";
	cout << "1. Tambah User\n";
	cout << "2. Cari User\n";
	cout << "3. Update User\n";
	cout << "4. Hapus User\n";
	cout << "5. Tampilkan Semua User\n";
	cout << "0. Keluar\n";
	cout << "==============================================\n";
	cout << "Pilih menu: ";
}

int main(){
	int pilihan;
	string id, nama;
	float t, h, n;
	int aq;
	bool s;

	do {
		tampilMenu();
		cin >> pilihan;

		if(pilihan == 1){
			cout << "-- Tambah User --\n";
			cout << "ID                       : "; 
			cin >> id;
			cout << "Nama                     : ";
			cin >> nama;
			cout << "Temperature (-10 s/d 50) : ";
			cin >> t;
			cout << "Humidity     (0 s/d 100) : ";
			cin >> h;
			cout << "Air Quality  (0 s/d 500) : ";
			cin >> aq;
			cout << "Smoke              (0/1) : ";
			cin >> s;
			cout << "Noise        (0 s/d 120) : ";
			cin >> n;
			insertUser(id, nama, t, h, aq, s, n);

		} else if(pilihan == 2){
			cout << "-- Cari User --\n";
			cout << "ID: ";
			cin >> id;
			cariUser(id);

		} else if(pilihan == 3){
			cout << "-- Update User --\n";
			cout << "ID: ";
			cin >> id;
			updateUserData(id);

		} else if(pilihan == 4){
			cout << "-- Hapus User --\n";
			cout << "ID: "; 
			cin >> id;
			deleteUser(id);

		} else if(pilihan == 5){
			showAll();

		} else if(pilihan == 0){
			cout << "Keluar dari sistem.\n";

		} else {
			cout << "Pilihan tidak valid.\n";
		}

	} while(pilihan != 0);

	return 0;
}