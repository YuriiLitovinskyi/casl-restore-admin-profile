#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// Current program will restore default admin profile for Casl Cloud: name: 'admin@casl.cloud', pass: 'admin'


int main(int argc, char *argv[]) {
	
    sqlite3 *db;
    char *err_msg = 0;
  
    
    // Open CASL DB
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open CASL Cloud database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        system("pause");
        
        return 1;
    }
    
    
    // query to delete existing admin profile
    char deleteAdmin[256] = "DELETE FROM user WHERE email = 'admin@casl.cloud'";
    
    rc = sqlite3_exec(db, deleteAdmin, 0, 0, &err_msg);   
      
    // query to insert default admin profile
    char restoreAdmin[256] = "INSERT INTO user (email, passw, last_name, first_name, middle_name, active_phone_id, role) VALUES " \
	                          "('admin@casl.cloud', '8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918', 'admin', 'admin', 'admin', NULL, 45)";
	                          
    rc = sqlite3_exec(db, restoreAdmin, 0, 0, &err_msg);
     
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        system("pause");
        
        return 1;
    } 
    
    sqlite3_close(db);  
    
    printf("\nDefault Admin profile was restored! \nName: 'admin@casl.cloud', password: 'admin' \n\n");
    
    system("pause");   
       
	return 0;
}
