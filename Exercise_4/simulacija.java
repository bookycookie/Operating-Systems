import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class simulacija {
	static String[] ramPomoc = new String[100];
	static List<String> RAM = Arrays.asList(ramPomoc);
	static int new_process_id = 0;
	
		public static void main(String[] args) {
			System.out.println(RAM.size());
			initRAM(RAM);
			printRAM(RAM);
			Scanner scanIn = new Scanner(System.in);
			String akcija;
			String process_id;
			int process_block_size;
			do {
				System.out.println("My next akcija is: ");
				akcija = scanIn.nextLine();
				
				if (akcija.equals("R") || akcija.equals("r"))
				{
					System.out.println("Enter new process block size: ");
					process_block_size = scanIn.nextInt();
					requestProcess(RAM, process_block_size);
				}
				else if(akcija.equals("F") || akcija.equals("f"))
				{
					System.out.println("Enter ID of the freeing process: ");
					process_id = scanIn.nextLine();
					freeProcess(RAM, process_id);
				}
				
				
				else if(akcija.equals("C") || akcija.equals("c"))
				{
					clearRAM(RAM);
				}
				
				
				else if(akcija.equals("D") || akcija.equals("d"))
				{
					defragmentRAM(RAM);
				}
				else if(!(akcija.equals("E") && akcija.equals("e")))
				{
					//System.out.println("Invalid operation, please try again!\n");
				}
				
			} while(!(akcija.equals("E") && akcija.equals("e")));
			
			System.out.println("End of simulation.\n");
			scanIn.close();
			return;
			}
		
		private static void initRAM(List<String> RAM) {			
			for(int i = 0; i < RAM.size(); i++) {
				RAM.set(i, "-");
			}
		}
		
		static void printRAM(List<String> RAM) {
					
					int i;
					for(i = 0; i < RAM.size(); i++) {
						System.out.print(((i%10)));
					}
					System.out.println();
					
					
					for(i = 0; i < RAM.size(); i++) {
						System.out.print(RAM.get(i));
					}
					
					System.out.println("\n");
			}
		
		static void requestProcess(List<String> RAM, int block_size) {
			
			System.out.println("Requesting a new process of size " + block_size + " and ID " + new_process_id);
			int start = 0;
			boolean freeBlockFound = false;
			int freeSize = 0;
			
			
			
			for(String elem : RAM) {
				if(elem.equals("-")) {
					start = RAM.indexOf("-");
					freeSize++;
				}
		}
		if(freeSize >= block_size) freeBlockFound = true;
		
		
		if(freeBlockFound) {
			for(int k = start; k < start + block_size; k++) {
				RAM.set(k, String.valueOf(new_process_id));
			}
			
			printRAM(RAM);
			System.out.println("Free block found! Reserved RAM for the process of size " + block_size + " and ID " + new_process_id);
			new_process_id++;
		}
		
		else {
			printRAM(RAM);
			System.out.println("There was no free block for a process of size " + block_size);
		}
}
		
		
		static void freeProcess(List<String> RAM, String process_id) {
			System.out.println("Searching for process with ID " + process_id + " to free...");
			boolean processFound = false;
			
			for(int i = 0; i < RAM.size(); i++) {
				if(RAM.get(i).equals(process_id)) {
					processFound = true;
					
					do {						
						RAM.set(i, "-");
						i++;
					} while(RAM.get(i).equals(process_id));
					
					break;
				}
			}
			
			printRAM(RAM);
			
			if(processFound) {
				System.out.println("Process with ID " + process_id + " successfully freed from RAM!");
			} else {
				System.out.println("Process with ID " + process_id + " was not found in RAM.");
			}
		}
		
		static void clearRAM(List<String> RAM) {
			System.out.println("Clearing the RAM...\n");
			freeRAM(RAM);
			printRAM(RAM);
			System.out.println("RAM successfully cleared!\n");
		}
		
		static void freeRAM(List<String> RAM) {
			for(int i = 0; i < RAM.size(); i++) {
				RAM.set(i, "-");
				new_process_id = 0;
			}
					
		}
		
		static void defragmentRAM(List<String> RAM) {
			int counter = 0;
			for(int i = 0; i < RAM.size(); i++) {
				if(!(RAM.get(i).equals("-"))) {
					if(counter != i) {
						RAM.set(counter, RAM.get(i));
						RAM.set(i, "-");
					}
					counter++;
				}
			}
			
			printRAM(RAM);
			System.out.println("Successfully defragmented RAM!\n");
		}
}
