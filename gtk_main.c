#include <gtk/gtk.h>
#include <stdbool.h>
#include "function.h"
#include <ctype.h>

void removeNonPrintableChars(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (isprint((unsigned char)str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

void on_fileImportButton_clicked(GtkWidget *button, gpointer textField)
{
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Open text file", GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(textField))), action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        FILE *file = fopen(filename, "r");
        if (file != NULL)
        {
            GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textField));
            gtk_text_buffer_set_text(buffer, "", 0);
            GtkTextIter iter;
            gtk_text_buffer_get_end_iter(buffer, &iter);

            char line[256];
            while (fgets(line, sizeof(line), file) != NULL)
            {
                gtk_text_buffer_insert(buffer, &iter, line, -1);
            }

            fclose(file);
        }
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

void on_button_clicked(GtkWidget *button, gpointer data)
{
    bool english;
    bool encode;

    GtkWidget **radio_buttons = (GtkWidget **)data; // Get pointer from data

    gboolean state1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_buttons[0]));
    gboolean state2 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_buttons[1]));
    GtkWidget *textview = radio_buttons[2];

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    if(state1 == TRUE)
        english = true;
    else
        english = false;

    if(state2 == TRUE)
        encode = true;
    else
        encode = false;
    
    char input[strlen(text) + 1];
    sprintf(input, "%s\n", text); // convert gchar to string (char array)
    //sprintf(input, sizeof(input), "%s\n", text);
    gchar* output = mainFunction(english, encode, input);
    gtk_text_buffer_set_text(buffer, "", 0);
    gchar* cleanedOutput = g_strchomp(output); // Remove trailing newline
    removeNonPrintableChars(cleanedOutput);
    gtk_text_buffer_insert_at_cursor(buffer, cleanedOutput, -1);
    g_free(text);
}

void on_export_clicked(GtkWidget *button, gpointer data) {
    GtkWidget *textview = data;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    const gchar *filename = "output.txt";

    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "%s", text);
        fclose(file);
    } else {
        g_print("Error opening file %s.\n", filename);
    }
}


int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    // Window init & properties
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Huffman Encoding");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 365);
    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // First section UI elements
    GtkWidget *labelLanguage = gtk_label_new("Select language:");
    gtk_label_set_xalign(GTK_LABEL(labelLanguage), 0.0); // Align text to the left
    GtkWidget *radioButtonEN = gtk_radio_button_new_with_label(NULL, "English");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioButtonEN), TRUE); // Set default option
    GtkWidget *radioButtonFR = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radioButtonEN), "French");
    GtkWidget *labelCoding = gtk_label_new("Select coding type:");
    gtk_label_set_xalign(GTK_LABEL(labelCoding), 0.0);
    GtkWidget *radioButtonEncoding = gtk_radio_button_new_with_label(NULL, "Encoding");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioButtonEncoding), TRUE);
    GtkWidget *radioButtonDecoding = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radioButtonEncoding), "Decoding");

    // Second section UI elements
    GtkWidget *hseparator1 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    GtkWidget *fileImportButton = gtk_button_new_with_label("Import File");
    GtkWidget *textField = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textField), GTK_WRAP_WORD);
    GtkWidget *scrollWindow = gtk_scrolled_window_new(NULL, NULL); // Make text field scrollable
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrollWindow, -1, 170);
    gtk_container_add(GTK_CONTAINER(scrollWindow), textField);

    // Third section UI elements
    GtkWidget *hseparator2 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    GtkWidget *button = gtk_button_new_with_label("Encode/Decode");
    GtkWidget *button2 = gtk_button_new_with_label("Export File");

    GtkWidget *hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5); // Horizontal box for the language radio buttons
    gtk_container_add(GTK_CONTAINER(hbox1), radioButtonEN);
    gtk_container_add(GTK_CONTAINER(hbox1), radioButtonFR);
    GtkWidget *hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5); // Horizontal box for the coding radio buttons
    gtk_container_add(GTK_CONTAINER(hbox2), radioButtonEncoding);
    gtk_container_add(GTK_CONTAINER(hbox2), radioButtonDecoding);
    GtkWidget *hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5); // Horizontal box for the third section
    gtk_container_add(GTK_CONTAINER(hbox3), button);
    gtk_box_pack_end(GTK_BOX(hbox3), button2, FALSE, FALSE, 0);
    // Main vertical container
    GtkWidget *vboxMain = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(vboxMain), labelLanguage);
    gtk_container_add(GTK_CONTAINER(vboxMain), hbox1);
    gtk_container_add(GTK_CONTAINER(vboxMain), labelCoding);
    gtk_container_add(GTK_CONTAINER(vboxMain), hbox2);
    gtk_container_add(GTK_CONTAINER(vboxMain), hseparator1);
    gtk_container_add(GTK_CONTAINER(vboxMain), fileImportButton);
    gtk_container_add(GTK_CONTAINER(vboxMain), scrollWindow);
    gtk_container_add(GTK_CONTAINER(vboxMain), hseparator2);
    gtk_container_add(GTK_CONTAINER(vboxMain), hbox3);

    // On-Click actions
    g_signal_connect(fileImportButton, "clicked", G_CALLBACK(on_fileImportButton_clicked), textField);
    GtkWidget *radio_buttons[3] = {radioButtonEN, radioButtonEncoding, textField}; // Array of pointers to use in function
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), radio_buttons);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_export_clicked), textField);

    gtk_container_add(GTK_CONTAINER(window), vboxMain);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

// sometimes random chars at end, newline not taken into account anymore