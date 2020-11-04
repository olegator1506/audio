import { Component, OnInit } from '@angular/core';
import {MatDialog, MatDialogRef, MAT_DIALOG_DATA} from '@angular/material/dialog';
import {ArrayDataSource} from '@angular/cdk/collections';
import {NestedTreeControl} from '@angular/cdk/tree';
import { DacRqService } from '../dac-rq.service';
import { MatTreeNestedDataSource } from '@angular/material/tree';
interface FileNode {
  name: string;
  path: string,
  folder:boolean,
  size:number,
  children?: FileNode[];
}

interface FileResponse {
  data : FileNode[];
}



@Component({
  selector: 'app-file-dialog',
  templateUrl: './file-dialog.component.html',
  styleUrls: ['./file-dialog.component.css'],
  providers: [DacRqService]
})

export class FileDialogComponent implements OnInit {
  rootNode : FileNode = {
    name:"ROOT",
    path:"/home/artem/",
    size:0,
    folder:true,
    children:[
      {name:'node1',path:'/xxx/yyy',folder:false,size:1024}
    ]
  }
  treeControl : NestedTreeControl<FileNode>;
  dataSource : ArrayDataSource<FileNode>;
  constructor(
    public dialogRef: MatDialogRef<FileDialogComponent>,
//    @Inject(MAT_DIALOG_DATA) public data: SoundControlConfig,
    private rqService : DacRqService
  ) {
    this.treeControl = new NestedTreeControl<FileNode>(node => this.rootNode.children);
    this.dataSource = new ArrayDataSource<FileNode>(this.rootNode.children);
//    this.dataSource = new MatTreeNestedDataSource(this.rootNode.children);

   }
   ngOnInit(){
    this.rqService.request("cmd=files&path=/home/artem/")
    .subscribe((resp : FileResponse) =>{
      this.rootNode.children = resp.data;
      this.treeControl = new NestedTreeControl<FileNode>(node => this.rootNode.children);
      this.dataSource = new ArrayDataSource(this.rootNode.children);
    });


   }

  hasChild = (_: number, node: FileNode) => !!node.children && node.children.length > 0;
}
