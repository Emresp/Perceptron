#include <stdio.h>
#include <stdlib.h>
#include "Perceptron.h"

int main(void)
{

    printf("Welcome to Perceptron learning system!\n\n");
    //Kaç tur eğitim yapması gerektiğini söyeleyen değişken
    int epoch_sayisi;

    int error_count;

    //Eğitim verileri and öğrettiğimiz varsayarak 4 tane farklı senaryo üzerinden öğreniyor
    double training_inputs[4][2] = {
        {0.0, 0.0}, // Makina bu iki değeri çarpar toplar ona göre ağrılık günceller
        {0.0, 1.0},
        {1.0, 0.0},
        {1.0, 1.0}
    };

    //Etiketli Öğrenme biçimi yaptığımız için 4 senaryonun sonucunu söylüyoruz
    int targets[4] = {0, 0, 0, 1};

    //Nörnomuzu yani perceptronumuzu yapay zeka adında oadres tutucak biçimde oluşturduk ve
    //2 tane girdi alacağını ve öğrenme hassaiyetinin (lr) 0.1 olduğunu fonksiyona girdik
    Perceptron *yapay_zeka = create_perceptron(2, 0.1);

    // Kaç tur Eğitim yapması gerektiğini girdim
    epoch_sayisi = 20;

    load_model(yapay_zeka);

    //Epoch sayısı kadar eğitim yapabilmesi için for oluşturdum
    for (int epoch=0 ; epoch < epoch_sayisi; epoch++)
    {
        error_count = 0;

        for (int i = 0; i < 4; i++)
        {
            // Makinamız öğrendiği zaman boş turlar atmasını engellemek için kontrol
            if (targets[i] != predict(yapay_zeka, training_inputs[i]))
            {
                error_count++;
            }
        }
        if (error_count==0)
        {
            printf("Makine Ogrenmesi %d. turda tamamlandi\n\n",epoch+1);

            //Öğrenme gerçekleştirilince değerleri kaybetmemek için kalıcı bir biçimde kayıt ediyoruz
            save_model(yapay_zeka);

            break;
        }

        for (int j = 0; j < 4; j++)
        {
            train(yapay_zeka,training_inputs[j],targets[j]);
        }
    }



    printf("--- TEST ASAMASI ---\n");

    //Hedeflenen çıktı ile makinaın öğrenip kendi yaptığı son tahmini karşılaştırdık
    for (int i = 0; i < 4; i++)
    {
        int sonuc = predict(yapay_zeka, training_inputs[i]);

        printf("Girdi: [%.1f, %.1f] -> Beklenen: %d | YZ sonucu : %d\n",
               training_inputs[i][0], training_inputs[i][1], targets[i], sonuc);
    }

    free(yapay_zeka->weights);
    free(yapay_zeka);

    return 0;
}