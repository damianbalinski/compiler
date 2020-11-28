int data_offset = 0;
int code_offset = 0;

/* Rezerwacja miejsca w segmecie danych,
   zwraca adres zarezerwowanej pamieci */
int data_location() {
    return data_offset++;
}


/* Rezerwacja pamieci w segmencie kodu,
   zwraca adres zarezerwowanej pamieci */
int reserve_loc() {
    return code_offset++;
}

int gen_label() {
    return code_offset;
}

/* Generowanie kodu w bierzacym przesunieciu */
void gen_code( enum code_ops operation, int arg ) {
    code[code_offset].op    = operation;
    code[code_offset++].arg = arg;
}

/* Generowanie kodu w podanym przesunieciu */
void back_patch( int addr,  enum code_ops operation, int arg ) {
    code[addr].op  = operation;
    code[addr].arg = arg;
}

void print_code() {
    int i = 0;
    while (i < code_offset) {
        printf("%3ld: %-10s%4ld\n", i, op_name[(int) code[i].op], code[i].arg );
        i++;
    }
}