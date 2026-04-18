#include <stdio.h>
#include <stdlib.h>
#include "Perceptron.h"

int main(void)
{
    int choice;

    printf("Welcome to Perceptron learning system!\n\n");
    while (choice != 3)
    {
        process_selection();
        printf("Please enter your choice: ");
        scanf("%d",&choice);

        if (choice == 1)
        {
            //Kaç tur eğitim yapması gerektiğini söyeleyen değişken
            int epoch_sayisi;

            int error_count;

            //Eğitim verileri and öğrettiğimiz varsayarak 4 tane farklı senaryo üzerinden öğreniyor
            double training_inputs[][2] = {
                {6.0, 7.0}, // Makina bu iki değeri çarpar toplar ona göre ağrılık günceller
                {5.0, 6.0},
                {2.0, 3.0},
                {1.0, 4.0}
            };

            //Etiketli Öğrenme biçimi yaptığımız için 4 senaryonun sonucunu söylüyoruz
            int targets[] = {1, 1, 0, 0};

            //Elaman sayısını bir değişkende tutuyorum ki üst taraflarda bir değişiklik yaptığım zaman döngüler otomatik hazır olsunlar
            //Verimizin sayısı
            int sample_count = sizeof(targets) / sizeof(targets[0]);

            //Nörnomuzu yani perceptronumuzu yapay zeka adında oadres tutucak biçimde oluşturduk ve
            //2 tane girdi alacağını ve öğrenme hassaiyetinin (lr) 0.1 olduğunu fonksiyona girdik
            Perceptron *yapay_zeka = create_perceptron(2, 0.1);

            // Kaç tur Eğitim yapması gerektiğini girdim
            epoch_sayisi = 100;

            load_model(yapay_zeka);

            //Epoch sayısı kadar eğitim yapabilmesi için for oluşturdum
            for (int epoch=0 ; epoch < epoch_sayisi; epoch++)
            {
                error_count = 0;

                for (int i = 0; i < sample_count; i++)
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

                for (int j = 0; j < sample_count; j++)
                {
                    train(yapay_zeka,training_inputs[j],targets[j]);
                }
            }



            printf("--- TEST ASAMASI ---\n");

            //Hedeflenen çıktı ile makinaın öğrenip kendi yaptığı son tahmini karşılaştırdık
            for (int i = 0; i < sample_count; i++)
            {
                int sonuc = predict(yapay_zeka, training_inputs[i]);

                printf("Input: [%.1f, %.1f] -> Expected: %d | YZ Result : %d\n",
                       training_inputs[i][0], training_inputs[i][1], targets[i], sonuc);
            }

            free(yapay_zeka->weights);
            free(yapay_zeka);
        }
        else if (choice == 2)
        {
            Perceptron *test_model = create_perceptron(2, 0.1);

            load_model(test_model);

            double test_student[2];
            int result;

            printf("Welcome to Predict system\n");

            printf("Enter the student's study hours:");
            scanf("%lf",&test_student[0]);

            printf("Enter the student's sleep hour:");
            scanf("%lf",&test_student[1]);

            result=predict(test_model,test_student);

            if (result==1)
            {
                printf("This student will pass the exam.\n\n");
            }
            else
            {
                printf("This student will not pass the exam.\n\n");
            }

            free(test_model->weights);
            free(test_model);
        }
        else if (choice == 3)
        {
            break;
        }
    }


    return 0;
}