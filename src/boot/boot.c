extern void app();

__attribute__((section(".boot")))
void __boot()
{
    // Initialize whatever you want

    app();
}

