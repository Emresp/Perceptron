#ifndef PERCEPTRON_PERCEPTRON_H
#define PERCEPTRON_PERCEPTRON_H


typedef struct
{
    double* weights; //Katsayılar, ağrılıklar
    double bias; //sabit modelin öncedn ne kadar meyilli olduğunu gösterir
    double learning_rate; //öğrenme değeri tahminlerimiz yenilierken ne kadar değişeceğini söylüyormuş gibi düşünebiliriz, hasasiyet
    int input_count; // kaç tane girdi alacağını belirtiriz
}Perceptron;

//Programımızın verimli çalışması için bize bu fonksiyon Perceptron türünde bir adres dönüyor
//Perceptron türü zaten yukarıda struct içinde tanımlı
//İki tane parametre alan bu fonksiyon inputs ve lr yani learning rate adında parametereler alır
Perceptron* create_perceptron(int inputs, double lr);

//Predict tahmin karar verme fonksiyonu
//Bu fonksiyon iki tane parametre alır ilk parametre olan *p paramtersi oluşturduğumuz percepron modelinin adresini alır
//İkinci parametremiz *inputs bir dizinin başlangıç adresini alır. Yani bunun kullanış amacı veri almaktır
//Veriler ve Percepronumuz ile bir tahmin oluşturmak için bu fonksiyon vardır
int predict(Perceptron* p, double* inputs );

//Train yani eğtim iyi bizim makina öğrenmesi dediğimiz kısım burada gerçekleşiyor
//bu fonksiyonda çıkması gereken(target) sonuçtan predict fonksiyonun yaptığı tahmin çıkartılır
//Bu işlem sonucunda hata payı(error) elde edilir bu elde ettiğimiz hata payı ile ağrıklarımızı tekrar güncelleriz
//ta ki hedef=tahmin olana kadar işte o zaman makine öğrenmiş olur
void train(Perceptron* p, double* inputs, int target);

//Modeli Kaydetmek için fonksiyon
void save_model(Perceptron* model);

//Modelin yüklemek için fonksiyon
void load_model(Perceptron* model);

//Giriş Ekranını göstermesi için
void process_selection();


#endif //PERCEPTRON_PERCEPTRON_H