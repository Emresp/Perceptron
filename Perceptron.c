#include <stdio.h>
#include <stdlib.h>
#include "Perceptron.h"

Perceptron* create_perceptron(int inputs, double lr)
{
    //malloc fonksiyonunda açılan yeri Perceptron* ifadesi ile adres olarak istedik ve new_perceptron değişkeninde
    //adres olarak tutabildim
    Perceptron* new_perceptron=(Perceptron*)malloc(sizeof(Perceptron));

    //yeni nöronumuz (perceptron'umuz) kaç tane girdi alıcak onun atamasını yaptım
    new_perceptron->input_count=inputs;
    //Aynı şekilde bu nöron'un (perceptron'un) leraning rate büyüklüğünü atadım
    new_perceptron->learning_rate=lr;

    //Weights değeri için her input kadar double türünde ramde yer açtık ve bunun adresini double* ifadesi ile alabildim
    new_perceptron->weights=(double*)malloc(sizeof(double)*inputs);

    //Başta Weights değerlerini rastgele atamak için for döngüsü
    for (int i=0;i<new_perceptron->input_count;i++)
    {
        //C dilindeki rand fonksiyonu ilkel olduğu için direk -1.0 ile 1.0 arasında değer üretemiyorum ondan dolayı
        //Matematiksel bölme ve çarpma işlmeleri ile değeri bu aralığa indiriyorum artık oluşan her değer -1.0 ile +1.0 arasında oluyor
        new_perceptron->weights[i]=((double)rand()/(double)RAND_MAX)*2.0-1.0;
    }

    //Aynı şekilde bias değerinide başlangıçta rastgele olucak şekilde atadım
    new_perceptron->bias = ((double)rand() / RAND_MAX) * 2.0 - 1.0;

    return new_perceptron;
}

int predict(Perceptron* p, double* inputs )
{
    //ağrılık*verilerin toplamını tutabilmek için
    double weight_sum=0.0;

    //Sırasıyla tüm ağırlıkları(katsayıları) verileirim ile çarpıyorum
    for (int i=0;i<p->input_count;i++)
    {
        //yapılan işlemleri topluyorum
        weight_sum= (double )weight_sum+(p->weights[i]*inputs[i]);
    }

    //toplam değeri sabit değerimi (bias'ı) ekliyorum
    weight_sum=p->bias+weight_sum;

    //Karar mekanizması bir kara varmasını sağlıyorum
    if (weight_sum>=0.0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void train(Perceptron* p, double* inputs, int target)
{
    int prediction;
    double error;

    //tahmin yapılır
    prediction=predict(p, inputs);

    //Hedefelenen tahmin çıkartılır ve hata payı bulunur
    error=(double)target-prediction;

    //Hatamız 0 değilse yani ağırlıkları(katsayıları) yenilememiz lazım
    if (error!=0.0)
    {
        //Her katsayıyı yenilemek için for döngüsü
        for (int i=0;i<p->input_count;i++)
        {
            //Perceptron ağrılık güncelleme formülü
            //// Yeni Ağırlık = Eski Ağırlık + (Hata *  Girdi * Öğrenme Hızı)
            p->weights[i]=(double) p->weights[i]+(error*inputs[i]*p->learning_rate);
        }

        //bias gücelleme
        p->bias=(double) p->bias+(error*p->learning_rate);
    }
}


void save_model(Perceptron* model)
{
    FILE* file=fopen("saved_model.txt","w");

    if (file==NULL)
    {
        printf("Saved model could not be opened");
        return;
    }

    fprintf(file, "%d\n", model->input_count);

    for (int i=0;i<model->input_count;i++)
    {
        fprintf(file,"%lf\n",model->weights[i]);
    }
    fprintf(file,"%lf\n",model->bias);

    fclose(file);

    printf("saved_model.txt saved\n");
}

void load_model(Perceptron* model)
{
    FILE* file=fopen("saved_model.txt","r");
    int file_input_count;

    if (file==NULL)
    {
        printf("Saved model could not be find\n");
        return;
    }

    fscanf(file, "%d", &file_input_count);

    if (file_input_count != model->input_count) {
        printf("HATA: Dosyadaki model %d girdili ama siz %d girdili bir yer açtınız!\n",
                file_input_count, model->input_count);
        return;
    }

    for (int i=0;i<model->input_count;i++)
    {
        fscanf(file,"%lf\n",&model->weights[i]);
    }

    fscanf(file,"%lf\n",&model->bias);

    fclose(file);

    printf("saved_model.txt load\n");
}

void process_selection()
{
    printf("1-) Train\n");
    printf("2-) Predict\n");
    printf("3-) exit\n");
}

Perceptron* load_model_from_file(const char* filename)
{
    //Perceptron Bilgilerinin kayıtlı olduğu dosya okuma modunda açılır
    FILE* file=fopen(filename,"r");
    //Dosyada bulunan girdi sayısını tutabilmek için değişkenm
    int file_input_count;

    //Dosya bulunamazsa NULL değeri dön
    if (file==NULL)
    {
        printf("Saved model could not be find\n");
        return NULL;
    }

    //Dosyada ilk değeri oku ve kayıt et
    fscanf(file, "%d", &file_input_count);

    //Girdi sayısına göre nöronu oluştur
    Perceptron* model=create_perceptron(file_input_count,0.1);

    //Ağırlıkları oku ve oluşturduğun Perceptronun içine yaz
    for (int i=0;i<model->input_count;i++)
    {
        fscanf(file,"%lf",&model->weights[i]);
    }

    //Aynı şekilde bias'ı oku ve yaz
    fscanf(file,"%lf",&model->bias);

    //Dosyayı kapat
    fclose(file);

    //Oluşan modeli dışarı dön
    return model;
}